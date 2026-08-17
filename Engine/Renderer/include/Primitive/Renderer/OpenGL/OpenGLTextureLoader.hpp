#pragma once

#include "Primitive/Resources/IResourceLoader.hpp"

namespace primitive
{
    class OpenGLTextureLoader final
        : public IResourceLoader
    {
    public:
        std::shared_ptr<Resource> Load(
            const std::filesystem::path& path
        ) override;
    };
}