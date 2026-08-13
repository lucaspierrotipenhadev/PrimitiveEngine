#pragma once

#include "Primitive/Resources/IResourceLoader.hpp"
#include "Primitive/Tests/TestResource.hpp"

namespace primitive
{
    class TestResourceLoader final : public IResourceLoader
    {
    public:
        std::shared_ptr<Resource> Load(
            const std::filesystem::path& path) override;
    };
}