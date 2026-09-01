#include "Primitive/Assets/AssetRegistry.hpp"

namespace primitive
{
    bool AssetRegistry::Register(const AssetMetadata& metadata)
    {
        if(!metadata.IsValid())
        {
            return false;
        }

        if(Contains(metadata.handle))
        {
            return false;
        }

        if(Contains(metadata.relativePath))
        {
            return false;
        }

        m_assets.emplace(metadata.handle, metadata);
        m_pathIndex.emplace(metadata.relativePath, metadata.handle);

        return true;
    }

    bool AssetRegistry::Contains(AssetHandle handle) const
    {
        return m_assets.find(handle) != m_assets.end();
    }

    bool AssetRegistry::Contains(const std::filesystem::path& relativePath) const
    {
        return m_pathIndex.find(relativePath) != m_pathIndex.end();
    }

    const AssetMetadata* AssetRegistry::GetMetadata(AssetHandle handle) const
    {
        const auto iterator = m_assets.find(handle);

        if (iterator == m_assets.end())
        {
            return nullptr;
        }

        return &iterator->second;
    }

    AssetHandle AssetRegistry::FindByPath(const std::filesystem::path& relativePath) const
    {
        const auto iterator = m_pathIndex.find(relativePath);

        if (iterator == m_pathIndex.end())
        {
            return InvalidAssetHandle;
        }

        return iterator->second;
    }

    std::size_t AssetRegistry::Count() const
    {
        return m_assets.size();
    }

    void AssetRegistry::Clear()
    {
        m_assets.clear();
        m_pathIndex.clear();
    }

    bool AssetRegistry::Remove(AssetHandle handle)
    {
        const auto iterator = m_assets.find(handle);
        
        if(iterator == m_assets.end())
        {
            return false;
        }

        m_pathIndex.erase(iterator->second.relativePath);
        m_assets.erase(iterator);

        return true;
    }
}