#include "Primitive/Renderer/OpenGL/OpenGLIndexBuffer.hpp"

#include <glad/gl.h>

#include <stdexcept>

namespace primitive
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(
        const std::uint32_t* indices,
        std::uint32_t count)
        : m_count(count)
    {
        if (indices == nullptr && count > 0)
        {
            throw std::invalid_argument(
                "OpenGLIndexBuffer received null indices."
            );
        }

        glCreateBuffers(
            1,
            &m_rendererID
        );

        glNamedBufferData(
            m_rendererID,
            static_cast<GLsizeiptr>(
                count * sizeof(std::uint32_t)
            ),
            indices,
            GL_STATIC_DRAW
        );
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        if (m_rendererID != 0)
        {
            glDeleteBuffers(
                1,
                &m_rendererID
            );
        }
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            m_rendererID
        );
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(
            GL_ELEMENT_ARRAY_BUFFER,
            0
        );
    }

    std::uint32_t
    OpenGLIndexBuffer::GetCount() const
    {
        return m_count;
    }
}