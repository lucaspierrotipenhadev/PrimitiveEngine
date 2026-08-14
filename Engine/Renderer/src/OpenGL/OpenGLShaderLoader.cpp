#include "Primitive/Renderer/OpenGL/OpenGLShaderLoader.hpp"

#include <stdexcept>
#include <string>

#include "Primitive/Core/FileSystem.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLShader.hpp"

namespace primitive
{
    namespace
    {
        struct ShaderSources
        {
            std::string vertex;
            std::string fragment;
        };

        ShaderSources ParseShaderSource(
            const std::string& source)
        {
            ShaderSources result;

            const std::string vertexToken =
                "#type vertex";

            const std::string fragmentToken =
                "#type fragment";

            const std::size_t vertexPos =
                source.find(vertexToken);

            const std::size_t fragmentPos =
                source.find(fragmentToken);

            if (vertexPos == std::string::npos)
            {
                throw std::runtime_error(
                    "Shader is missing '#type vertex'."
                );
            }

            if (fragmentPos == std::string::npos)
            {
                throw std::runtime_error(
                    "Shader is missing '#type fragment'."
                );
            }

            if (fragmentPos <= vertexPos)
            {
                throw std::runtime_error(
                    "Invalid shader stage order."
                );
            }

            const std::size_t vertexStart =
                vertexPos + vertexToken.length();

            result.vertex =
                source.substr(
                    vertexStart,
                    fragmentPos - vertexStart
                );

            const std::size_t fragmentStart =
                fragmentPos + fragmentToken.length();

            result.fragment =
                source.substr(fragmentStart);

            return result;
        }
    }

    std::shared_ptr<Resource>
    OpenGLShaderLoader::Load(
        const std::filesystem::path& path)
    {
        const std::string source =
            FileSystem::ReadText(path);

        const ShaderSources sources =
            ParseShaderSource(source);

        return std::make_shared<OpenGLShader>(
            path.string(),
            sources.vertex,
            sources.fragment
        );
    }
}