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

        virtual void SetInt(
            std::string_view name,
            int value
        ) = 0;

        virtual void SetFloat(
            std::string_view name,
            float value
        ) = 0;

        virtual void SetFloat2(
            std::string_view name,
            float x,
            float y
        ) = 0;

        virtual void SetFloat3(
            std::string_view name,
            float x,
            float y,
            float z
        ) = 0;

        virtual void SetFloat4(
            std::string_view name,
            float x,
            float y,
            float z,
            float w
        ) = 0;

        virtual void SetMat4(
            std::string_view name,
            const float* value
        ) = 0;
    };
}