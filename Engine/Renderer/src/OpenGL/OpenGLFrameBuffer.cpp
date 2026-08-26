#include "Primitive/Renderer/OpenGL/OpenGLFramebuffer.hpp"

#include <glad/gl.h>

#include <stdexcept>

namespace primitive
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification &specification) : m_specification(specification)
    {
        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        if (m_depthAttachment)
        {
            glDeleteRenderbuffers(1, &m_depthAttachment);
        }

        if (m_colorAttachment)
        {
            glDeleteTextures(1, &m_colorAttachment);
        }

        if (m_rendererID)
        {
            glDeleteFramebuffers(1, &m_rendererID);
        }
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_rendererID)
        {
            glDeleteFramebuffers(1, &m_rendererID);
            glDeleteTextures(1, &m_colorAttachment);
            glDeleteRenderbuffers(1, &m_depthAttachment);

            m_rendererID = 0;
            m_colorAttachment = 0;
            m_depthAttachment = 0;
        }

        glCreateFramebuffers(1, &m_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

        // Color attachment
        glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);

        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, static_cast<GLsizei>(m_specification.width), static_cast<GLsizei>(m_specification.height), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(
            GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            m_colorAttachment,
            0);

        // Depth attachment
        glCreateRenderbuffers(
            1,
            &m_depthAttachment);

        glBindRenderbuffer(
            GL_RENDERBUFFER,
            m_depthAttachment);

        glRenderbufferStorage(
            GL_RENDERBUFFER,
            GL_DEPTH24_STENCIL8,
            static_cast<GLsizei>(
                m_specification.width),
            static_cast<GLsizei>(
                m_specification.height));

        glFramebufferRenderbuffer(
            GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER,
            m_depthAttachment);

        if (glCheckFramebufferStatus(
                GL_FRAMEBUFFER) !=
            GL_FRAMEBUFFER_COMPLETE)
        {
            throw std::runtime_error(
                "OpenGL framebuffer is incomplete.");
        }

        glBindFramebuffer(
            GL_FRAMEBUFFER,
            0);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            m_rendererID);

        glViewport(
            0,
            0,
            static_cast<GLsizei>(
                m_specification.width),
            static_cast<GLsizei>(
                m_specification.height));
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(
            GL_FRAMEBUFFER,
            0);
    }

    void OpenGLFramebuffer::Resize(
        std::uint32_t width,
        std::uint32_t height)
    {
        if (width == 0 ||
            height == 0)
        {
            return;
        }

        if (m_specification.width == width &&
            m_specification.height == height)
        {
            return;
        }

        m_specification.width =
            width;

        m_specification.height =
            height;

        Invalidate();
    }

    std::uint32_t
    OpenGLFramebuffer::GetColorAttachmentID() const
    {
        return m_colorAttachment;
    }

    const FramebufferSpecification &
    OpenGLFramebuffer::GetSpecification() const
    {
        return m_specification;
    }
}