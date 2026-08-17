#include "Primitive/Resources/ModelLoader.hpp"

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Primitive/Renderer/Mesh.hpp"
#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Renderer/Renderer.hpp"
#include "Primitive/Renderer/Vertex.hpp"
#include "Primitive/Renderer/VertexBufferLayout.hpp"

namespace primitive
{
    std::unique_ptr<Mesh> ProcessMesh(
        const aiMesh *mesh,
        Renderer &renderer)
    {
        std::vector<Vertex> vertices;
        std::vector<std::uint32_t> indices;

        vertices.reserve(
            mesh->mNumVertices);

        for (unsigned int i = 0;
             i < mesh->mNumVertices;
             ++i)
        {
            Vertex vertex;

            // Position
            vertex.position =
                {
                    mesh->mVertices[i].x,
                    mesh->mVertices[i].y,
                    mesh->mVertices[i].z};

            // Normal
            if (mesh->HasNormals())
            {
                vertex.normal =
                    {
                        mesh->mNormals[i].x,
                        mesh->mNormals[i].y,
                        mesh->mNormals[i].z};
            }

            // UV
            if (mesh->mTextureCoords[0])
            {
                vertex.texCoord =
                    {
                        mesh->mTextureCoords[0][i].x,
                        mesh->mTextureCoords[0][i].y};
            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0;
             i < mesh->mNumFaces;
             ++i)
        {
            const aiFace &face =
                mesh->mFaces[i];

            for (unsigned int j = 0;
                 j < face.mNumIndices;
                 ++j)
            {
                indices.push_back(
                    static_cast<std::uint32_t>(
                        face.mIndices[j]));
            }
        }

        VertexBufferLayout layout;

        layout.Push(
            ShaderDataType::Float3); // position

        layout.Push(
            ShaderDataType::Float3); // normal

        layout.Push(
            ShaderDataType::Float2); // texCoord

        return renderer.CreateMesh(
            vertices.data(),
            vertices.size() * sizeof(Vertex),
            layout,
            indices.data(),
            static_cast<std::uint32_t>(
                indices.size()));
    }

    ModelLoader::ModelLoader(
        Renderer &renderer)
        : m_renderer(renderer)
    {
    }

    std::shared_ptr<Resource>
    ModelLoader::Load(
        const std::filesystem::path &path)
    {
        Assimp::Importer importer;

        const aiScene *scene =
            importer.ReadFile(
                path.string(),
                aiProcess_Triangulate |
                    aiProcess_GenSmoothNormals |
                    aiProcess_JoinIdenticalVertices);

        if (!scene)
        {
            throw std::runtime_error(
                std::string(
                    "Failed to load model: ") +
                importer.GetErrorString());
        }

        if (!scene->mRootNode)
        {
            throw std::runtime_error(
                "Loaded model has no root node.");
        }

        auto model =
            std::make_shared<Model>(
                path.string());

        for (unsigned int i = 0;
             i < scene->mNumMeshes;
             ++i)
        {
            const aiMesh *mesh =
                scene->mMeshes[i];

            model->AddMesh(
                ProcessMesh(
                    mesh,
                    m_renderer));
        }

        return model;
    }

}