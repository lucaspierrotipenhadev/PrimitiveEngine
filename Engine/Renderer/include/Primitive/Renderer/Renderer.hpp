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
    class Mesh;
    class VertexBufferLayout;
    class Model;
    class Material;
    struct FramebufferSpecification;
    class Framebuffer;

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

        void DepthTest(bool enable);

        void Clear(float r, float g, float b, float a);
        void Draw(std::uint32_t vertexCount);
        void DrawIndexed(const IndexBuffer &indexBuffer);
        void DrawMesh(const Mesh &mesh);
        void DrawModel(const Model &model, const Material &material);

        std::unique_ptr<VertexBuffer>
        CreateVertexBuffer(
            const void *data,
            std::size_t size);

        std::unique_ptr<IndexBuffer>
        CreateIndexBuffer(
            const std::uint32_t *indices,
            std::uint32_t count);

        std::unique_ptr<VertexArray>
        CreateVertexArray();

        std::unique_ptr<Mesh>
        CreateMesh(
            const void *vertices,
            std::size_t vertexSize,
            const VertexBufferLayout &layout,
            const std::uint32_t *indices,
            std::uint32_t indexCount);

        [[nodiscard]]
        std::unique_ptr<Framebuffer>
        CreateFramebuffer(
            const FramebufferSpecification &specification);

        void SetViewport( std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height);

    private:
        std::unique_ptr<IRendererAPI> m_api;
        std::unique_ptr<IRendererFactory> m_factory;
    };
}