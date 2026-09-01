#pragma once

#include "Primitive/Assets/Importers/IAssetImporter.hpp"

namespace primitive
{
    class ShaderAssetImporter final : public IAssetImporter
    {
    public:
        [[nodiscard]]
        AssetType GetAssetType() const override;

        [[nodiscard]]
        bool CanImport(const std::filesystem::path& sourcePath) const override;
    };
}