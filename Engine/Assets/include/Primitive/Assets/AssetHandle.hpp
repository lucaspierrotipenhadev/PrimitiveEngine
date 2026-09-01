#pragma once

#include <cstdint>

namespace primitive
{
    using AssetHandle = std::uint64_t;

    inline constexpr AssetHandle InvalidAssetHandle{0};
}