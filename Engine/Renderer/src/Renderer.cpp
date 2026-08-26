#include "Primitive/Renderer/Renderer.hpp"

#include <stdexcept>

#include "Primitive/Core/Configuration.hpp"

#include "Primitive/Resources/ResourceManager.hpp"

#include "Primitive/Renderer/Mesh.hpp"
#include "Primitive/Renderer/Texture.hpp"
#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/Material.hpp"

#include "Primitive/Renderer/IRendererAPI.hpp"
#include "Primitive/Renderer/IRendererFactory.hpp"

#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/IndexBuffer.hpp"
#include "Primitive/Renderer/VertexBufferLayout.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLRendererFactory.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLIndexBuffer.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLFramebuffer.hpp"

namespace primitive
{
    namespace
    {
        std::unique_ptr<IRendererFactory>
        CreateRendererFactory(
            RendererBackend backend)
        {
            switch (backend)
            {
            case RendererBackend::OpenGL:
                return std::make_unique<
                    OpenGLRendererFactory>();

            default:
                throw std::runtime_error(
                    "Unsupported renderer backend.");
            }
        }
    }

    Renderer::Renderer() = default;
    Renderer::~Renderer() = default;

    void Renderer::Initialize(
        RendererBackend backend,
        ResourceManager &resourceManager)
    {
        if (m_api || m_factory)
        {
            throw std::runtime_error(
                "Renderer is already initialized.");
        }

        m_factory =
            CreateRendererFactory(backend);

        m_api =
            m_factory->CreateRendererAPI();

        if (!m_api)
        {
            throw std::runtime_error(
                "Renderer factory failed to create Renderer API.");
        }

        m_api->Initialize();

        auto shaderLoader =
            m_factory->CreateShaderLoader();

        auto textureLoader =
            m_factory->CreateTextureLoader();

        if (!shaderLoader)
        {
            throw std::runtime_error("Renderer factory failed to create shader loader");
        }

        resourceManager.RegisterLoader<Shader>(std::move(shaderLoader));
        resourceManager.RegisterLoader<Texture>(std::move(textureLoader));
    }

    void Renderer::Shutdown()
    {
        if (m_api)
        {
            m_api->Shutdown();
            m_api.reset();
        }

        m_factory.reset();
    }

    void Renderer::BeginFrame()
    {
        if (m_api)
        {
            m_api->BeginFrame();
        }
    }

    void Renderer::EndFrame()
    {
        if (m_api)
        {
            m_api->EndFrame();
        }
    }

    void Renderer::DepthTest(bool enable)
    {
        if (m_api)
        {
            m_api->SetDepthTest(enable);
        }
    }

    void Renderer::Clear(
        float r,
        float g,
        float b,
        float a)
    {
        if (m_api)
        {
            m_api->Clear(
                r,
                g,
                b,
                a);
        }
    }

    void Renderer::Draw(
        std::uint32_t vertexCount)
    {
        if (m_api)
        {
            m_api->Draw(vertexCount);
        }
    }

    void Renderer::DrawIndexed(
        const IndexBuffer &indexBuffer)
    {
        if (m_api)
        {
            m_api->DrawIndexed(
                indexBuffer.GetCount());
        }
    }

    void Renderer::DrawMesh(const Mesh &mesh)
    {
        mesh.Bind();

        DrawIndexed(mesh.GetIndexBuffer());

        mesh.Unbind();
    }

    void Renderer::DrawModel(
        const Model &model,
        const Material &material)
    {
        const auto &shader = material.GetShader();
        shader->Bind();

        const glm::vec4 &color = material.GetBaseColor();

        shader->SetFloat4("u_Color", color.r, color.g, color.b, color.a);
        if (material.GetAlbedoTexture())
        {
            material.GetAlbedoTexture()->Bind(0);

            shader->SetInt(
                "u_AlbedoTexture",
                0);

            shader->SetInt(
                "u_HasAlbedoTexture",
                1);
        }
        else
        {
            shader->SetInt(
                "u_HasAlbedoTexture",
                0);
        }

        for (const auto &mesh :
             model.GetMeshes())
        {
            DrawMesh(
                *mesh);
        }

        shader->Unbind();
    }

    std::unique_ptr<VertexBuffer>
    Renderer::CreateVertexBuffer(
        const void *data,
        std::size_t size)
    {
        if (!m_factory)
        {
            throw std::runtime_error(
                "Renderer is not initialized.");
        }

        return m_factory->CreateVertexBuffer(
            data,
            size);
    }

    std::unique_ptr<VertexArray>
    Renderer::CreateVertexArray()
    {
        if (!m_factory)
        {
            throw std::runtime_error(
                "Renderer is not initialized.");
        }

        return m_factory->CreateVertexArray();
    }

    std::unique_ptr<IndexBuffer>
    Renderer::CreateIndexBuffer(
        const std::uint32_t *indices,
        std::uint32_t count)
    {
        if (!m_factory)
        {
            throw std::runtime_error(
                "Renderer is not initialized.");
        }

        return m_factory->CreateIndexBuffer(
            indices,
            count);
    }

    std::unique_ptr<Mesh>
    Renderer::CreateMesh(
        const void *vertices,
        std::size_t vertexSize,
        const VertexBufferLayout &layout,
        const std::uint32_t *indices,
        std::uint32_t indexCount)
    {
        auto vertexBuffer =
            CreateVertexBuffer(
                vertices,
                vertexSize);

        auto indexBuffer =
            CreateIndexBuffer(
                indices,
                indexCount);

        auto vertexArray =
            CreateVertexArray();

        vertexArray->AddVertexBuffer(
            *vertexBuffer,
            layout);

        vertexArray->SetIndexBuffer(
            *indexBuffer);

        return std::make_unique<Mesh>(
            std::move(vertexArray),
            std::move(vertexBuffer),
            std::move(indexBuffer));
    }

    std::unique_ptr<Framebuffer>
    Renderer::CreateFramebuffer(
        const FramebufferSpecification &specification)
    {
        return m_factory->CreateFramebuffer(
            specification);
    }

    void Renderer::SetViewport(
        std::uint32_t x,
        std::uint32_t y,
        std::uint32_t width,
        std::uint32_t height)
    {
        m_api->SetViewport(
            x,
            y,
            width,
            height);
    }
}