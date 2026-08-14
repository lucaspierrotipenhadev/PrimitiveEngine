#include "Primitive/Renderer/OpenGL/OpenGLRendererFactory.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLRenderer.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLShaderLoader.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLVertexBuffer.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLVertexArray.hpp"

namespace primitive
{
    std::unique_ptr<IRendererAPI>
    OpenGLRendererFactory::CreateRendererAPI()
    {
        return std::make_unique<OpenGLRenderer>();
    }

    std::unique_ptr<VertexBuffer>
    OpenGLRendererFactory::CreateVertexBuffer(
        const void* data,
        std::size_t size)
    {
        return std::make_unique<OpenGLVertexBuffer>(
            data,
            size
        );
    }

    std::unique_ptr<VertexArray>
    OpenGLRendererFactory::CreateVertexArray()
    {
        return std::make_unique<OpenGLVertexArray>();
    }

    std::shared_ptr<IResourceLoader>
    OpenGLRendererFactory::CreateShaderLoader()
    {
        return std::make_shared<OpenGLShaderLoader>();
    }
}