#pragma once

#include <cstdint>

#include "Primitive/Renderer/IndexBuffer.hpp"

namespace primitive
{
    class OpenGLIndexBuffer final
        : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(
            const std::uint32_t* indices,
            std::uint32_t count
        );

        ~OpenGLIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        [[nodiscard]]
        std::uint32_t GetCount() const override;

    private:
        unsigned int m_rendererID{0};
        std::uint32_t m_count{0};
    };
}