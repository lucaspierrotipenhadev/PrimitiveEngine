#include "Primitive/Assets/Importers/ModelAssetImporter.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace primitive
{
    AssetType
    ModelAssetImporter::GetAssetType() const
    {
        return AssetType::Model;
    }

    bool ModelAssetImporter::CanImport(const std::filesystem::path& sourcePath) const
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

        return
            extension == ".fbx" ||
            extension == ".obj" ||
            extension == ".gltf" ||
            extension == ".glb";
    }
}