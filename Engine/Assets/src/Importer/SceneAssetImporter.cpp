#include "Primitive/Assets/Importers/SceneAssetImporter.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace primitive
{
    AssetType SceneAssetImporter::GetAssetType() const
    {
        return AssetType::Scene;
    }

    bool SceneAssetImporter::CanImport(const std::filesystem::path& sourcePath) const
    {
        std::string extension = sourcePath.extension().string();

        std::transform(
            extension.begin(),
            extension.end(),
            extension.begin(),
            [](unsigned char character)
            {
                return static_cast<char>(
                    std::tolower(character)
                );
            }
        );

        return extension == ".pscene";
    }
}