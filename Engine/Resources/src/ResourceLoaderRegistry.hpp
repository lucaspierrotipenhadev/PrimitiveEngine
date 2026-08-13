#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Primitive/Resources/IResourceLoader.hpp"

namespace primitive
{
    class ResourceLoaderRegistry
    {
    public:
        ResourceLoaderRegistry() = default;
        ~ResourceLoaderRegistry() = default;

        ResourceLoaderRegistry(const ResourceLoaderRegistry&) = delete;
        ResourceLoaderRegistry& operator=(
            const ResourceLoaderRegistry&) = delete;

        template<typename T>
        void Register(std::shared_ptr<IResourceLoader> loader)
        {
            const auto typeKey =
                std::type_index(typeid(T));

            m_loaders[typeKey] = std::move(loader);
        }

        template<typename T>
        std::shared_ptr<IResourceLoader> Get() const
        {
            const auto typeKey =
                std::type_index(typeid(T));

            const auto it =
                m_loaders.find(typeKey);

            if (it == m_loaders.end())
            {
                return nullptr;
            }

            return it->second;
        }

        template<typename T>
        bool Has() const
        {
            const auto typeKey =
                std::type_index(typeid(T));

            return m_loaders.contains(typeKey);
        }

        void Clear()
        {
            m_loaders.clear();
        }

    private:
        std::unordered_map<
            std::type_index,
            std::shared_ptr<IResourceLoader>
        > m_loaders;
    };
}