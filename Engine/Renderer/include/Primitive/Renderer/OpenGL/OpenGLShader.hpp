#pragma once

#include "Primitive/Renderer/Shader.hpp"

namespace primitive
{
    class OpenGLShader final : public Shader
    {
    public:
        explicit OpenGLShader(std::string_view filepath);
        ~OpenGLShader() override;

        void Bind() override;
        void Unbind() override;

    private:
        unsigned int m_program{0};
    };
}