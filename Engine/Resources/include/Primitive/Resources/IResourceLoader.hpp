#pragma once

#include <filesystem>
#include <memory>

#include "Primitive/Resources/Resource.hpp"

namespace primitive
{
    class IResourceLoader
    {
    public:
        virtual ~IResourceLoader() = default;

        virtual std::shared_ptr<Resource> Load(
            const std::filesystem::path& path) = 0;
    };
}