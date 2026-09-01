#pragma once

#include <cstdint>

namespace primitive
{
    enum class AssetType : std::uint8_t
    {
        None = 0,
        Scene,
        Model,
        Texture,
        Material,
        Shader,
        Script,
        Animation
    };
}