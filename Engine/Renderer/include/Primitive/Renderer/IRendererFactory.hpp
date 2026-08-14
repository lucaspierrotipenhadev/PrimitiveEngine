#pragma once

#include <cstddef>
#include <memory>

namespace primitive
{
    class IRendererAPI;
    class IResourceLoader;
    class VertexBuffer;
    class VertexArray;

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

        virtual std::shared_ptr<IResourceLoader>
        CreateShaderLoader() = 0;
    };
}