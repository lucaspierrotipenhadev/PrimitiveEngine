#pragma once

#include <filesystem>

#include "Primitive/Assets/AssetHandle.hpp"
#include "Primitive/Assets/AssetType.hpp"

namespace primitive
{
    struct AssetMetadata
    {
        AssetHandle handle{InvalidAssetHandle};
        AssetType type{AssetType::None};
        std::filesystem::path relativePath;

        [[nodiscard]]
        bool IsValid() const
        {
            return handle != InvalidAssetHandle && type != AssetType::None && !relativePath.empty();
        }
    };
    
}