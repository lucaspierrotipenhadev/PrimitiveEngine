#pragma once

#include <cstdint>
#include <string_view>

#include "Primitive/Renderer/Texture.hpp"

namespace primitive
{
    class OpenGLTexture final
        : public Texture
    {
    public:
        OpenGLTexture(
            std::string_view filepath,
            std::uint32_t width,
            std::uint32_t height,
            std::uint32_t channels,
            const unsigned char* data
        );

        ~OpenGLTexture() override;

        void Bind(
            std::uint32_t slot = 0
        ) const override;

        void Unbind() const override;

        [[nodiscard]]
        std::uint32_t GetWidth() const override;

        [[nodiscard]]
        std::uint32_t GetHeight() const override;

    private:
        unsigned int m_rendererID{0};

        std::uint32_t m_width{0};
        std::uint32_t m_height{0};
    };
}