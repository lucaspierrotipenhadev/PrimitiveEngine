#include "Primitive/Assets/AssetManager.hpp"

#include "Primitive/Assets/AssetHandleGenerator.hpp"

namespace primitive
{
    AssetManager::AssetManager(const Project &project, ResourceManager &resourceManager) : m_project(project), m_resourceManager(resourceManager)
    {
    }

    template <typename T> requires std::derived_from<T, Resource>
    std::shared_ptr<T> AssetManager::GetLoadedAsset(AssetHandle handle, AssetType expectedType) const
    {
        const AssetMetadata *metadata = ResolveMetadata(handle, expectedType);

        if (!metadata)
        {
            return nullptr;
        }

        const std::filesystem::path filepath = m_project.GetAssetPath(metadata->relativePath);

        return m_resourceManager.Get<T>(filepath.string());
    }

    AssetHandle AssetManager::RegisterAsset(AssetType type, const std::filesystem::path &relativePath)
    {
        if (type == AssetType::None)
        {
            return InvalidAssetHandle;
        }

        if (relativePath.empty())
        {
            return InvalidAssetHandle;
        }

        const AssetHandle existingHandle = m_registry.FindByPath(relativePath);

        if (existingHandle != InvalidAssetHandle)
        {
            return existingHandle;
        }

        AssetHandle handle = InvalidAssetHandle;

        do
        {
            handle = AssetHandleGenerator::Generate();
        } while (m_registry.Contains(handle));

        AssetMetadata metadata;

        metadata.handle = handle;
        metadata.type = type;
        metadata.relativePath = relativePath;

        if (!m_registry.Register(metadata))
        {
            return InvalidAssetHandle;
        }

        return handle;
    }

    bool AssetManager::RemoveAsset(AssetHandle handle)
    {
        return m_registry.Remove(handle);
    }

    bool AssetManager::Contains(AssetHandle handle) const
    {
        return m_registry.Contains(handle);
    }

    bool AssetManager::Contains(const std::filesystem::path &relativePath) const
    {
        return m_registry.Contains(relativePath);
    }

    const AssetMetadata *AssetManager::GetMetadata(AssetHandle handle) const
    {
        return m_registry.GetMetadata(handle);
    }

    AssetHandle AssetManager::FindByPath(const std::filesystem::path &relativePath) const
    {
        return m_registry.FindByPath(relativePath);
    }

    std::size_t AssetManager::GetAssetCount() const
    {
        return m_registry.Count();
    }

    const AssetRegistry &AssetManager::GetRegistry() const
    {
        return m_registry;
    }

    void AssetManager::Clear()
    {
        m_registry.Clear();
    }

    const AssetMetadata *AssetManager::ResolveMetadata(AssetHandle handle, AssetType expectedType) const
    {
        if (handle == InvalidAssetHandle)
        {
            return nullptr;
        }

        const AssetMetadata *metadata = m_registry.GetMetadata(handle);

        if (!metadata)
        {
            return nullptr;
        }

        if (!metadata->IsValid())
        {
            return nullptr;
        }

        if (metadata->type != expectedType)
        {
            return nullptr;
        }

        return metadata;
    }
}