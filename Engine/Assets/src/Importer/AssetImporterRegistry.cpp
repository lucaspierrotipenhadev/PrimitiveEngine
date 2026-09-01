#include "Primitive/Assets/Importers/AssetImporterRegistry.hpp"

#include <utility>

#include "Primitive/Assets/Importers/IAssetImporter.hpp"

namespace primitive
{
    void AssetImporterRegistry::Register(std::unique_ptr<IAssetImporter> importer)
    {
        if (!importer)
        {
            return;
        }

        m_importers.emplace_back(std::move(importer));
    }

    const IAssetImporter* AssetImporterRegistry::FindImporter(const std::filesystem::path& sourcePath) const
    {
        for (const auto& importer : m_importers)
        {
            if (importer->CanImport(sourcePath))
            {
                return importer.get();
            }
        }

        return nullptr;
    }

    AssetType AssetImporterRegistry::ResolveAssetType(const std::filesystem::path& sourcePath) const
    {
        const IAssetImporter* importer = FindImporter(sourcePath);

        if (!importer)
        {
            return AssetType::None;
        }

        return importer->GetAssetType();
    }

    std::size_t AssetImporterRegistry::Count() const
    {
        return m_importers.size();
    }

    void AssetImporterRegistry::Clear()
    {
        m_importers.clear();
    }
}