#pragma once

#include <filesystem>
#include <unordered_map>

#include "Primitive/Assets/AssetHandle.hpp"
#include "Primitive/Assets/AssetMetadata.hpp"

namespace primitive
{
    class AssetRegistry
    {
    public:
        [[nodiscard]]
        bool Register(const AssetMetadata& metadata);

        [[nodiscard]]
        bool Remove(AssetHandle handle) const;

        [[nodiscard]]
        bool Contains(AssetHandle handle) const;

        [[nodiscard]]
        bool Contains(const std::filesystem::path& relativePath) const;

        [[nodiscard]]
        const AssetMetadata* GetMetadata(AssetHandle handle) const;

        [[nodiscard]]
        AssetHandle FindByPath(const std::filesystem::path& relativePath) const;

        [[nodiscard]]
        std::size_t Count() const;

        void Clear();

        bool Remove(AssetHandle handle);

    private:
        std::unordered_map<AssetHandle, AssetMetadata> m_assets;
        std::unordered_map<std::filesystem::path, AssetHandle> m_pathIndex;
    };
}