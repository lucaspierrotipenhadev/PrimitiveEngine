#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include "Primitive/Renderer/Shader.hpp"

namespace primitive
{
    class OpenGLShader final : public Shader
    {
    public:
        OpenGLShader(
            std::string_view filepath,
            std::string_view vertexSource,
            std::string_view fragmentSource
        );

        ~OpenGLShader() override;

        void Bind() override;
        void Unbind() override;

        void SetInt(
            std::string_view name,
            int value
        ) override;

        void SetFloat(
            std::string_view name,
            float value
        ) override;

        void SetFloat2(
            std::string_view name,
            float x,
            float y
        ) override;

        void SetFloat3(
            std::string_view name,
            float x,
            float y,
            float z
        ) override;

        void SetFloat4(
            std::string_view name,
            float x,
            float y,
            float z,
            float w
        ) override;

        void SetMat4(
            std::string_view name,
            const float* value
        ) override;

    private:
        unsigned int m_program{0};

        int GetUniformLocation(
            std::string_view name
        );

        std::unordered_map<std::string, int>
        m_uniformLocationCache;
    };
}