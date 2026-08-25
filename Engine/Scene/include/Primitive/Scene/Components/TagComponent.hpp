#pragma once

#include <string>
#include <utility>

namespace primitive
{
    struct TagComponent
    {
        std::string tag;

        TagComponent() = default;

        explicit TagComponent(std::string value)
            : tag(std::move(value))
        {
        }
    };
}