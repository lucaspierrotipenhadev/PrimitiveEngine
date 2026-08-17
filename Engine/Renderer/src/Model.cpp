#include "Primitive/Renderer/Model.hpp"

#include <stdexcept>
#include <utility>

#include "Primitive/Renderer/Mesh.hpp"

namespace primitive
{
    Model::Model(
        std::string_view filepath)
        : Resource(filepath)
    {
    }

    Model::~Model() = default;

    Model::Model(
        Model &&) noexcept = default;

    Model &Model::operator=(
        Model &&) noexcept = default;

    void Model::AddMesh(
        std::unique_ptr<Mesh> mesh)
    {
        if (!mesh)
        {
            throw std::invalid_argument(
                "Cannot add null Mesh to Model.");
        }

        m_meshes.push_back(
            std::move(mesh));
    }

    std::size_t
    Model::GetMeshCount() const
    {
        return m_meshes.size();
    }

    const Mesh &
    Model::GetMesh(
        std::size_t index) const
    {
        if (index >= m_meshes.size())
        {
            throw std::out_of_range(
                "Model mesh index out of range.");
        }

        return *m_meshes[index];
    }

    Mesh &
    Model::GetMesh(
        std::size_t index)
    {
        if (index >= m_meshes.size())
        {
            throw std::out_of_range(
                "Model mesh index out of range.");
        }

        return *m_meshes[index];
    }

    const std::vector<
        std::unique_ptr<Mesh>> &
    Model::GetMeshes() const
    {
        return m_meshes;
    }
}