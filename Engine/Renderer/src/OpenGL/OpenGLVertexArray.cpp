#include "Primitive/Renderer/OpenGL/OpenGLVertexArray.hpp"

#include <glad/gl.h>

#include <stdexcept>

#include "Primitive/Renderer/IndexBuffer.hpp"

namespace primitive
{
    namespace
    {
        GLenum ShaderDataTypeToOpenGL(
            ShaderDataType type)
        {
            switch (type)
            {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
                return GL_FLOAT;

            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;

            default:
                throw std::runtime_error(
                    "Unsupported ShaderDataType."
                );
            }
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(
            1,
            &m_rendererID
        );
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        if (m_rendererID != 0)
        {
            glDeleteVertexArrays(
                1,
                &m_rendererID
            );
        }
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(
            m_rendererID
        );
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(
        const VertexBuffer& vertexBuffer,
        const VertexBufferLayout& layout)
    {
        Bind();
        vertexBuffer.Bind();

        const auto& elements =
            layout.GetElements();

        for (const auto& element : elements)
        {
            glEnableVertexAttribArray(
                m_vertexAttributeIndex
            );

            glVertexAttribPointer(
                m_vertexAttributeIndex,
                static_cast<GLint>(
                    element.count
                ),
                ShaderDataTypeToOpenGL(
                    element.type
                ),
                element.normalized
                    ? GL_TRUE
                    : GL_FALSE,
                static_cast<GLsizei>(
                    layout.GetStride()
                ),
                reinterpret_cast<const void*>(
                    static_cast<std::uintptr_t>(
                        element.offset
                    )
                )
            );

            ++m_vertexAttributeIndex;
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(
        const IndexBuffer& indexBuffer
    )
    {
        Bind();
        indexBuffer.Bind();
    }
}