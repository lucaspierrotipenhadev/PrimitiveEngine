#pragma once

#include <filesystem>
#include <memory>

#include "Primitive/Resources/IResourceLoader.hpp"

namespace primitive
{
    class OpenGLShaderLoader final : public IResourceLoader
    {
    public:
        std::shared_ptr<Resource> Load(
            const std::filesystem::path& path
        ) override;
    };
}