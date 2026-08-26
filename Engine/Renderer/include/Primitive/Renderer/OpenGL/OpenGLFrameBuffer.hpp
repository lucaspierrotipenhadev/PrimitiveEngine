#pragma once

#include "Primitive/Renderer/Framebuffer.hpp"

namespace primitive
{
    class OpenGLFramebuffer final : public Framebuffer
    {
    public:
        explicit OpenGLFramebuffer(
            const FramebufferSpecification& specification
        );

        ~OpenGLFramebuffer() override;

        void Bind() override;
        void Unbind() override;

        void Resize(
            std::uint32_t width,
            std::uint32_t height
        ) override;

        [[nodiscard]]
        std::uint32_t GetColorAttachmentID() const override;

        [[nodiscard]]
        const FramebufferSpecification&
        GetSpecification() const override;

    private:
        void Invalidate();

    private:
        std::uint32_t m_rendererID{0};
        std::uint32_t m_colorAttachment{0};
        std::uint32_t m_depthAttachment{0};

        FramebufferSpecification m_specification;
    };
}