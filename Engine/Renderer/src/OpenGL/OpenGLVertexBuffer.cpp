#include "Primitive/Renderer/OpenGL/OpenGLVertexBuffer.hpp"

#include <glad/gl.h>

#include <stdexcept>

namespace primitive
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(
        const void* data,
        std::size_t size)
    {
        if (data == nullptr && size > 0)
        {
            throw std::invalid_argument(
                "OpenGLVertexBuffer received null data."
            );
        }

        glGenBuffers(
            1,
            &m_rendererID
        );

        glBindBuffer(
            GL_ARRAY_BUFFER,
            m_rendererID
        );

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(size),
            data,
            GL_STATIC_DRAW
        );
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        if (m_rendererID != 0)
        {
            glDeleteBuffers(
                1,
                &m_rendererID
            );
        }
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(
            GL_ARRAY_BUFFER,
            m_rendererID
        );
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(
            GL_ARRAY_BUFFER,
            0
        );
    }

    void OpenGLVertexBuffer::SetData(
        const void* data,
        std::size_t size)
    {
        if (data == nullptr && size > 0)
        {
            throw std::invalid_argument(
                "OpenGLVertexBuffer received null data."
            );
        }

        Bind();

        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(size),
            data,
            GL_STATIC_DRAW
        );
    }
}