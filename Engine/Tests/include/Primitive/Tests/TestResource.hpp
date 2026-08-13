#pragma once

#include "Primitive/Resources/Resource.hpp"

#include <string>
#include <filesystem>

namespace primitive
{
    class TestResource : public Resource
    {
    public:
        explicit TestResource(
            const std::filesystem::path& filepath,
            std::string content)
            : Resource(filepath.string()),
              m_content(std::move(content))
        {
        }

        [[nodiscard]]
        const std::string& GetContent() const
        {
            return m_content;
        }

    private:
        std::string m_content;
    };
}