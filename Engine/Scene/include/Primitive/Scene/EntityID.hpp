#pragma once

#include <cstdint>
#include <limits>

namespace primitive
{
    using EntityID = std::uint32_t;

    inline constexpr EntityID NullEntity =
        std::numeric_limits<EntityID>::max();
}