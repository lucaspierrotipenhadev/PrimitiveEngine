#pragma once

#include "Primitive/Renderer/VertexArray.hpp"

namespace primitive
{
    class OpenGLVertexArray final
        : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(
            const VertexBuffer& vertexBuffer,
            const VertexBufferLayout& layout
        ) override;

        void SetIndexBuffer(
            const IndexBuffer& IndexBuffer
        ) override;

    private:
        unsigned int m_rendererID{0};
        unsigned int m_vertexAttributeIndex{0};
    };
}