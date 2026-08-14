#pragma once

#include <memory>

namespace primitive
{
    class VertexBuffer;
    class IndexBuffer;
    class VertexArray;

    class Mesh
    {
    public:
        Mesh(
            std::unique_ptr<VertexArray> vertexArray,
            std::unique_ptr<VertexBuffer> vertexBuffer,
            std::unique_ptr<IndexBuffer> indexBuffer
        );

        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        Mesh(Mesh&&) noexcept;
        Mesh& operator=(Mesh&&) noexcept;

        void Bind() const;
        void Unbind() const;

        [[nodiscard]]
        const IndexBuffer& GetIndexBuffer() const;

    private:
        std::unique_ptr<VertexArray>
            m_vertexArray;

        std::unique_ptr<VertexBuffer>
            m_vertexBuffer;

        std::unique_ptr<IndexBuffer>
            m_indexBuffer;
    };
}