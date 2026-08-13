#pragma once

#include <string>
#include <string_view>

namespace primitive
{
    class Resource
    {
    public:
        explicit Resource(std::string_view filepath) : m_filepath(filepath) {}
        virtual ~Resource() = default;

        [[nodiscard]] const std::string& GetFilepath() const { return m_filepath; }

    private:
        std::string m_filepath;
    };
}