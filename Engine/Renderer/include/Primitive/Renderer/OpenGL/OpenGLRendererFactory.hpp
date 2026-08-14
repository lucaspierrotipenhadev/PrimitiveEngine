#pragma once

#include "Primitive/Renderer/IRendererFactory.hpp"

namespace primitive
{
    class OpenGLRendererFactory final
        : public IRendererFactory
    {
    public:
        std::unique_ptr<IRendererAPI>
        CreateRendererAPI() override;

        std::unique_ptr<VertexBuffer>
        CreateVertexBuffer(
            const void *data,
            std::size_t size) override;

        std::unique_ptr<VertexArray>
        CreateVertexArray() override;

        std::unique_ptr<IndexBuffer>
        CreateIndexBuffer(
            const std::uint32_t *indices,
            std::uint32_t count) override;

        std::shared_ptr<IResourceLoader>
        CreateShaderLoader() override;
    };
}