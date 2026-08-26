#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>

namespace primitive
{
    class IRendererAPI;
    class IResourceLoader;
    class VertexBuffer;
    class VertexArray;
    class IndexBuffer;
    class Texture;
    class Framebuffer;
    struct FramebufferSpecification;

    class IRendererFactory
    {
    public:
        virtual ~IRendererFactory() = default;

        IRendererFactory() = default;

        IRendererFactory(
            const IRendererFactory&) = delete;

        IRendererFactory& operator=(
            const IRendererFactory&) = delete;

        virtual std::unique_ptr<IRendererAPI>
        CreateRendererAPI() = 0;

        virtual std::unique_ptr<VertexBuffer>
        CreateVertexBuffer(
            const void* data,
            std::size_t size
        ) = 0;

        virtual std::unique_ptr<VertexArray>
        CreateVertexArray() = 0;

        virtual std::unique_ptr<IndexBuffer>
        CreateIndexBuffer(
            const std::uint32_t* indices,
            std::uint32_t count
        ) = 0;

        virtual std::shared_ptr<IResourceLoader>
        CreateShaderLoader() = 0;

        virtual std::shared_ptr<IResourceLoader>
        CreateTextureLoader() = 0;

        virtual std::unique_ptr<Framebuffer>
        CreateFramebuffer(
                const FramebufferSpecification& specification
        ) = 0;
    };
}