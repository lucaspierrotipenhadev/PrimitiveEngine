#include "Primitive/Assets/AssetDiscovery.hpp"

#include <filesystem>
#include <system_error>

#include "Primitive/Assets/AssetManager.hpp"
#include "Primitive/Assets/AssetType.hpp"
#include "Primitive/Assets/Importers/AssetImporterRegistry.hpp"

#include "Primitive/Project/Project.hpp"

namespace primitive
{
    AssetDiscoveryResult AssetDiscovery::Discover(const Project& project, AssetManager& assetManager, const AssetImporterRegistry& importerRegistry)
    {
        AssetDiscoveryResult result;

        if (!project.IsValid())
        {
            return result;
        }

        const std::filesystem::path assetsDirectory = project.GetAssetsDirectory();

        std::error_code error;

        if (!std::filesystem::exists(assetsDirectory, error) || error
        )
        {
            return result;
        }

        std::filesystem::recursive_directory_iterator iterator{
            assetsDirectory,
            std::filesystem::directory_options::skip_permission_denied,
            error
        };

        const std::filesystem::recursive_directory_iterator end;

        while (iterator != end && !error)
        {
            const auto& entry = *iterator;

            if (entry.is_regular_file(error))
            {
                ++result.filesScanned;

                const AssetType type = importerRegistry.ResolveAssetType(entry.path());

                if (type == AssetType::None)
                {
                    ++result.unsupportedFiles;
                    iterator.increment(error);
                    continue;
                }

                ++result.assetsDiscovered;

                std::filesystem::path relativePath = std::filesystem::relative(
                        entry.path(),
                        assetsDirectory,
                        error
                    );

                if (error)
                {
                    error.clear();
                    iterator.increment(error);
                    continue;
                }

                relativePath = relativePath.lexically_normal();

                const bool alreadyRegistered = assetManager.Contains(relativePath);
                const AssetHandle handle = assetManager.RegisterAsset(type, relativePath);

                if (handle != InvalidAssetHandle && !alreadyRegistered)
                {
                    ++result.assetsRegistered;
                }
            }

            iterator.increment(error);
        }

        return result;
    }
}