#pragma once

#include <memory>
#include <cstdint>
#include <cstddef>

namespace primitive
{
    class IRendererAPI;
    class IRendererFactory;
    class ResourceManager;
    class VertexBuffer;
    class VertexArray;
    class IndexBuffer;

    enum class RendererBackend;

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        Renderer(const Renderer &) = delete;
        Renderer &operator=(const Renderer &) = delete;

        void Initialize(RendererBackend backend, ResourceManager &resourceManager);
        void Shutdown();

        void BeginFrame();
        void EndFrame();

        void Clear(float r, float g, float b, float a);
        void Draw(std::uint32_t vertexCount);
        void DrawIndexed(const IndexBuffer& indexBuffer);

        std::unique_ptr<VertexBuffer>
        CreateVertexBuffer(
            const void *data,
            std::size_t size);

        std::unique_ptr<IndexBuffer>
        CreateIndexBuffer(
            const std::uint32_t* indices,
            std::uint32_t count
        );

        std::unique_ptr<VertexArray>
        CreateVertexArray();

    private:
        std::unique_ptr<IRendererAPI> m_api;
        std::unique_ptr<IRendererFactory> m_factory;
    };
}