#pragma once

#include <cstdint>
#include <string_view>

#include "Primitive/Resources/Resource.hpp"

namespace primitive
{
    class Texture : public Resource
    {
    public:
        explicit Texture(std::string_view filepath)
            : Resource(filepath)
        {
        }

        ~Texture() override = default;

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        virtual void Bind(
            std::uint32_t slot = 0
        ) const = 0;

        virtual void Unbind() const = 0;

        [[nodiscard]]
        virtual std::uint32_t GetWidth() const = 0;

        [[nodiscard]]
        virtual std::uint32_t GetHeight() const = 0;
    };
}