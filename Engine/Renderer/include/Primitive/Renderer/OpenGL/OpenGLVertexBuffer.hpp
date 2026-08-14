#pragma once

#include "Primitive/Renderer/VertexBuffer.hpp"

namespace primitive
{
    class OpenGLVertexBuffer final : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(
            const void* data,
            std::size_t size
        );

        ~OpenGLVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        void SetData(
            const void* data,
            std::size_t size
        ) override;

        [[nodiscard]]
        unsigned int GetRendererID() const
        {
            return m_rendererID;
        }

    private:
        unsigned int m_rendererID{0};
    };
}