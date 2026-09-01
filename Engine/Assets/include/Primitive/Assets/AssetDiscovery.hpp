#pragma once

#include <cstddef>

namespace primitive
{
    class AssetManager;
    class Project;
    class AssetImporterRegistry;

    struct AssetDiscoveryResult
    {
        std::size_t filesScanned{0};
        std::size_t assetsDiscovered{0};
        std::size_t assetsRegistered{0};
        std::size_t unsupportedFiles{0};
    };

    class AssetDiscovery
    {
    public:
        [[nodiscard]]
        static AssetDiscoveryResult Discover(const Project& project, AssetManager& assetManager, const AssetImporterRegistry& importerRegistry);
    };
}