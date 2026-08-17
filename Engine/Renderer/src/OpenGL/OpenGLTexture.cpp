#include "Primitive/Renderer/OpenGL/OpenGLTexture.hpp"

#include <glad/gl.h>

#include <stdexcept>

namespace primitive
{
    OpenGLTexture::OpenGLTexture(
        std::string_view filepath,
        std::uint32_t width,
        std::uint32_t height,
        std::uint32_t channels,
        const unsigned char* data)
        : Texture(filepath),
          m_width(width),
          m_height(height)
    {
        if (!data)
        {
            throw std::invalid_argument(
                "OpenGLTexture received null pixel data."
            );
        }

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;

        switch (channels)
        {
        case 1:
            internalFormat = GL_R8;
            dataFormat = GL_RED;
            break;

        case 3:
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
            break;

        case 4:
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
            break;

        default:
            throw std::runtime_error(
                "Unsupported texture channel count."
            );
        }

        glCreateTextures(
            GL_TEXTURE_2D,
            1,
            &m_rendererID
        );

        glTextureStorage2D(
            m_rendererID,
            1,
            internalFormat,
            static_cast<GLsizei>(m_width),
            static_cast<GLsizei>(m_height)
        );

        glTextureParameteri(
            m_rendererID,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR
        );

        glTextureParameteri(
            m_rendererID,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR
        );

        glTextureParameteri(
            m_rendererID,
            GL_TEXTURE_WRAP_S,
            GL_REPEAT
        );

        glTextureParameteri(
            m_rendererID,
            GL_TEXTURE_WRAP_T,
            GL_REPEAT
        );

        glTextureSubImage2D(
            m_rendererID,
            0,
            0,
            0,
            static_cast<GLsizei>(m_width),
            static_cast<GLsizei>(m_height),
            dataFormat,
            GL_UNSIGNED_BYTE,
            data
        );
    }

    OpenGLTexture::~OpenGLTexture()
    {
        if (m_rendererID != 0)
        {
            glDeleteTextures(
                1,
                &m_rendererID
            );
        }
    }

    void OpenGLTexture::Bind(
        std::uint32_t slot) const
    {
        glBindTextureUnit(
            slot,
            m_rendererID
        );
    }

    void OpenGLTexture::Unbind() const
    {
        // Com glBindTextureUnit, não há um
        // "slot atual" armazenado na Texture.
        // Podemos deixar vazio inicialmente.
    }

    std::uint32_t
    OpenGLTexture::GetWidth() const
    {
        return m_width;
    }

    std::uint32_t
    OpenGLTexture::GetHeight() const
    {
        return m_height;
    }
}