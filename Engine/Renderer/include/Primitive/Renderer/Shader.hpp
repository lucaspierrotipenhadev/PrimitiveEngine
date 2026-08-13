#pragma once

#include "Primitive/Resources/Resource.hpp"

namespace primitive
{
    class Shader : public Resource
    {
    public:
        explicit Shader(std::string_view filepath)
            : Resource(filepath)
        {
        }

        ~Shader() override = default;

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}