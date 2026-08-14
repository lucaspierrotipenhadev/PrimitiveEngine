#include "Primitive/Renderer/Mesh.hpp"

#include <stdexcept>
#include <utility>

#include "Primitive/Renderer/VertexArray.hpp"
#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/IndexBuffer.hpp"

namespace primitive
{
    Mesh::Mesh(
        std::unique_ptr<VertexArray> vertexArray,
        std::unique_ptr<VertexBuffer> vertexBuffer,
        std::unique_ptr<IndexBuffer> indexBuffer)
        : m_vertexArray(std::move(vertexArray)),
          m_vertexBuffer(std::move(vertexBuffer)),
          m_indexBuffer(std::move(indexBuffer))
    {
        if (!m_vertexArray)
        {
            throw std::invalid_argument(
                "Mesh requires a valid VertexArray."
            );
        }

        if (!m_vertexBuffer)
        {
            throw std::invalid_argument(
                "Mesh requires a valid VertexBuffer."
            );
        }

        if (!m_indexBuffer)
        {
            throw std::invalid_argument(
                "Mesh requires a valid IndexBuffer."
            );
        }
    }

    Mesh::~Mesh() = default;

    Mesh::Mesh(Mesh&&) noexcept = default;

    Mesh& Mesh::operator=(
        Mesh&&) noexcept = default;

    void Mesh::Bind() const
    {
        m_vertexArray->Bind();
    }

    void Mesh::Unbind() const
    {
        m_vertexArray->Unbind();
    }

    const IndexBuffer&
    Mesh::GetIndexBuffer() const
    {
        return *m_indexBuffer;
    }
}