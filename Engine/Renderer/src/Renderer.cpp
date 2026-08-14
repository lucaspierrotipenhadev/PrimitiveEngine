#include "Primitive/Renderer/Renderer.hpp"

#include <stdexcept>

#include "Primitive/Core/Configuration.hpp"

#include "Primitive/Resources/ResourceManager.hpp"

#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/IRendererAPI.hpp"
#include "Primitive/Renderer/IRendererFactory.hpp"

#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/IndexBuffer.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLRendererFactory.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLIndexBuffer.hpp"

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

        if (!shaderLoader)
        {
            throw std::runtime_error("Renderer factory failed to create shader loader");
        }

        resourceManager.RegisterLoader<Shader>(std::move(shaderLoader));
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
        const IndexBuffer& indexBuffer
    )
    {
        if(m_api)
        {
            m_api->DrawIndexed(
                indexBuffer.GetCount()
            );
        }
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
        const std::uint32_t* indices,
        std::uint32_t count
    )
    {
        if(!m_factory)
        {
            throw std::runtime_error(
                "Renderer is not initialized."
            );
        }

        return m_factory->CreateIndexBuffer(
            indices,
            count
        );
    }
}