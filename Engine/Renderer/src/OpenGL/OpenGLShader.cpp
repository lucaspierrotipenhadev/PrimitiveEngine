#include "Primitive/Renderer/OpenGL/OpenGLShader.hpp"

#include <glad/gl.h>

#include <stdexcept>
#include <string>

namespace primitive
{
    namespace
    {
        unsigned int CompileShader(
            unsigned int type,
            std::string_view source)
        {
            const unsigned int shader =
                glCreateShader(type);

            const char *sourceCode =
                source.data();

            glShaderSource(
                shader,
                1,
                &sourceCode,
                nullptr);

            glCompileShader(shader);

            int success = 0;

            glGetShaderiv(
                shader,
                GL_COMPILE_STATUS,
                &success);

            if (!success)
            {
                char infoLog[1024];

                glGetShaderInfoLog(
                    shader,
                    sizeof(infoLog),
                    nullptr,
                    infoLog);

                glDeleteShader(shader);

                throw std::runtime_error(
                    std::string(
                        "Failed to compile shader: ") +
                    infoLog);
            }

            return shader;
        }
    }

    OpenGLShader::OpenGLShader(
        std::string_view filepath,
        std::string_view vertexSource,
        std::string_view fragmentSource)
        : Shader(filepath)
    {
        const unsigned int vertexShader =
            CompileShader(
                GL_VERTEX_SHADER,
                vertexSource);

        const unsigned int fragmentShader =
            CompileShader(
                GL_FRAGMENT_SHADER,
                fragmentSource);

        m_program = glCreateProgram();

        glAttachShader(
            m_program,
            vertexShader);

        glAttachShader(
            m_program,
            fragmentShader);

        glLinkProgram(m_program);

        int success = 0;

        glGetProgramiv(
            m_program,
            GL_LINK_STATUS,
            &success);

        if (!success)
        {
            char infoLog[1024];

            glGetProgramInfoLog(
                m_program,
                sizeof(infoLog),
                nullptr,
                infoLog);

            glDeleteProgram(m_program);
            m_program = 0;

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            throw std::runtime_error(
                std::string(
                    "Failed to link shader program: ") +
                infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        if (m_program != 0)
        {
            glDeleteProgram(m_program);
        }
    }

    void OpenGLShader::Bind()
    {
        glUseProgram(m_program);
    }

    void OpenGLShader::Unbind()
    {
        glUseProgram(0);
    }

    int OpenGLShader::GetUniformLocation(
        std::string_view name)
    {
        const std::string uniformName{name};

        const auto it =
            m_uniformLocationCache.find(uniformName);

        if (it != m_uniformLocationCache.end())
        {
            return it->second;
        }

        const int location =
            glGetUniformLocation(
                m_program,
                uniformName.c_str());

        m_uniformLocationCache.emplace(
            uniformName,
            location);

        return location;
    }

    void OpenGLShader::SetInt(
        std::string_view name,
        int value)
    {
        glUniform1i(
            GetUniformLocation(name),
            value);
    }

    void OpenGLShader::SetFloat(
        std::string_view name,
        float value)
    {
        glUniform1f(
            GetUniformLocation(name),
            value);
    }

    void OpenGLShader::SetFloat2(
        std::string_view name,
        float x,
        float y)
    {
        glUniform2f(
            GetUniformLocation(name),
            x,
            y);
    }

    void OpenGLShader::SetFloat3(
        std::string_view name,
        float x,
        float y,
        float z)
    {
        glUniform3f(
            GetUniformLocation(name),
            x,
            y,
            z);
    }

    void OpenGLShader::SetFloat4(
        std::string_view name,
        float x,
        float y,
        float z,
        float w)
    {
        glUniform4f(
            GetUniformLocation(name),
            x,
            y,
            z,
            w);
    }

    void OpenGLShader::SetMat4(
        std::string_view name,
        const float *value)
    {
        glUniformMatrix4fv(
            GetUniformLocation(name),
            1,
            GL_FALSE,
            value);
    }
}