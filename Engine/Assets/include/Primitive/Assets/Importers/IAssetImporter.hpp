#pragma once

#include <filesystem>

#include "Primitive/Assets/AssetType.hpp"

namespace primitive
{
    class IAssetImporter
    {
    public:
        virtual ~IAssetImporter() = default;

        [[nodiscard]]
        virtual AssetType GetAssetType() const = 0;

        [[nodiscard]]
        virtual bool CanImport(const std::filesystem::path& sourcePath) const = 0;
    };
}