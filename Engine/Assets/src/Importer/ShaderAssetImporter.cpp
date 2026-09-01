#include "Primitive/Assets/Importers/ShaderAssetImporter.hpp"

#include <algorithm>
#include <cctype>
#include <string>

namespace primitive
{
    AssetType ShaderAssetImporter::GetAssetType() const
    {
        return AssetType::Shader;
    }

    bool ShaderAssetImporter::CanImport(const std::filesystem::path& sourcePath) const
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

        return extension == ".vert" || extension == ".frag" || extension == ".glsl";
    }
}