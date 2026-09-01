#include "Primitive/Assets/Importers/TextureAssetImporter.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace primitive
{
    AssetType TextureAssetImporter::GetAssetType() const
    {
        return AssetType::Texture;
    }

    bool TextureAssetImporter::CanImport(const std::filesystem::path& sourcePath) const
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
            extension == ".png" ||
            extension == ".jpg" ||
            extension == ".jpeg" ||
            extension == ".bmp" ||
            extension == ".tga";
    }
}