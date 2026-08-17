#include "Primitive/Renderer/OpenGL/OpenGLRendererFactory.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLRenderer.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLTextureLoader.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLShaderLoader.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLVertexBuffer.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLVertexArray.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLIndexBuffer.hpp"

namespace primitive
{
    std::unique_ptr<IRendererAPI>
    OpenGLRendererFactory::CreateRendererAPI()
    {
        return std::make_unique<OpenGLRenderer>();
    }

    std::unique_ptr<VertexBuffer>
    OpenGLRendererFactory::CreateVertexBuffer(
        const void *data,
        std::size_t size)
    {
        return std::make_unique<OpenGLVertexBuffer>(
            data,
            size);
    }

    std::unique_ptr<VertexArray>
    OpenGLRendererFactory::CreateVertexArray()
    {
        return std::make_unique<OpenGLVertexArray>();
    }

    std::unique_ptr<IndexBuffer>
    OpenGLRendererFactory::CreateIndexBuffer(
        const std::uint32_t *indices,
        std::uint32_t count)
    {
        return std::make_unique<OpenGLIndexBuffer>(
            indices,
            count);
    }

    std::shared_ptr<IResourceLoader>
    OpenGLRendererFactory::CreateShaderLoader()
    {
        return std::make_shared<OpenGLShaderLoader>();
    }

    std::shared_ptr<IResourceLoader>
    OpenGLRendererFactory::CreateTextureLoader()
    {
        return std::make_shared<
            OpenGLTextureLoader>();
    }
}