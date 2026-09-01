#pragma once

#include <filesystem>
#include <memory>
#include <concepts>

#include "Primitive/Assets/AssetHandle.hpp"
#include "Primitive/Assets/AssetMetadata.hpp"
#include "Primitive/Assets/AssetType.hpp"
#include "Primitive/Assets/AssetRegistry.hpp"

#include "Primitive/Project/Project.hpp"

#include "Primitive/Resources/ResourceManager.hpp"

namespace primitive
{
    class AssetManager
    {
    public:
        AssetManager(const Project &project, ResourceManager &resourceManager);

        [[nodiscard]]
        AssetHandle RegisterAsset(AssetType type, const std::filesystem::path &relativePath);

        [[nodiscard]]
        bool RemoveAsset(AssetHandle handle);

        [[nodiscard]]
        bool Contains(AssetHandle handle) const;

        [[nodiscard]]
        bool Contains(const std::filesystem::path &relativePath) const;

        [[nodiscard]]
        const AssetMetadata *GetMetadata(AssetHandle handle) const;

        [[nodiscard]]
        AssetHandle FindByPath(const std::filesystem::path &relativePath) const;

        [[nodiscard]]
        std::size_t GetAssetCount() const;

        [[nodiscard]]
        const AssetRegistry &GetRegistry() const;

        template <typename T>
            requires std::derived_from<T, Resource>
        [[nodiscard]]
        std::shared_ptr<T> LoadAsset(AssetHandle handle, AssetType expectedType)
        {
            const AssetMetadata *metadata = ResolveMetadata(handle, expectedType);

            if (!metadata)
            {
                return nullptr;
            }

            const std::filesystem::path filepath = m_project.GetAssetPath(metadata->relativePath);

            return m_resourceManager.Load<T>(filepath.string());
        }

        template <typename T>
            requires std::derived_from<T, Resource>
        [[nodiscard]]
        std::shared_ptr<T> GetLoadedAsset(AssetHandle handle, AssetType expectedType) const;

        void Clear();

    private:
        [[nodiscard]]
        const AssetMetadata *ResolveMetadata(AssetHandle handle, AssetType expectedType) const;

    private:
        const Project &m_project;
        ResourceManager &m_resourceManager;
        AssetRegistry m_registry;
    };
}