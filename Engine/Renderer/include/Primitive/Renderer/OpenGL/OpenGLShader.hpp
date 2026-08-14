#pragma once

#include <string>
#include <string_view>

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

    private:
        unsigned int m_program{0};
    };
}