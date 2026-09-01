#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include "Primitive/Assets/AssetType.hpp"

namespace primitive
{
    class IAssetImporter;

    class AssetImporterRegistry
    {
    public:
        void Register(std::unique_ptr<IAssetImporter> importer);

        [[nodiscard]]
        const IAssetImporter* FindImporter(const std::filesystem::path& sourcePath) const;

        [[nodiscard]]
        AssetType ResolveAssetType(const std::filesystem::path& sourcePath) const;

        [[nodiscard]]
        std::size_t Count() const;

        void Clear();

    private:
        std::vector<std::unique_ptr<IAssetImporter>> m_importers;
    };
}