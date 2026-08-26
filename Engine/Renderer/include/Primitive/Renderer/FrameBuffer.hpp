#pragma once

#include <cstdint>

namespace primitive
{
    struct FramebufferSpecification
    {
        std::uint32_t width{1280};
        std::uint32_t height{720};
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        Framebuffer() = default;

        Framebuffer(const Framebuffer&) = delete;
        Framebuffer& operator=(const Framebuffer&) = delete;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(
            std::uint32_t width,
            std::uint32_t height
        ) = 0;

        [[nodiscard]]
        virtual std::uint32_t GetColorAttachmentID() const = 0;

        [[nodiscard]]
        virtual const FramebufferSpecification&
        GetSpecification() const = 0;
    };
}