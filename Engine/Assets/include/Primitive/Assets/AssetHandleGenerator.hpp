#pragma once

#include "Primitive/Assets/AssetHandle.hpp"

namespace primitive
{
    class AssetHandleGenerator
    {
    public:
        [[nodiscard]]
        static AssetHandle Generate();
    };
}