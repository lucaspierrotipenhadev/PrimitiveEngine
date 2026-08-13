#pragma once

#include "Primitive/Resources/IResourceLoader.hpp"
#include "Primitive/Tests/TestResource.hpp"

namespace primitive
{
    class TestResourceLoader : public IResourceLoader
    {
    public:
        std::shared_ptr<Resource> Load(
            const std::string& filepath) override
        {
            const auto content =
                FileSystem::ReadText(filepath);

            return std::make_shared<TestResource>(
                filepath,
                content
            );
        }
    };
}