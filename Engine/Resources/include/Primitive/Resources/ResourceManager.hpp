#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <stdexcept>

#include "Primitive/Resources/Resource.hpp"
#include "Primitive/Resources/IResourceLoader.hpp"
#include "Primitive/Resources/ResourceLoaderRegistry.hpp"

namespace primitive
{
    template<typename T>
    concept IsResource = std::derived_from<T, Resource>;

    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        template<IsResource T>
        void RegisterLoader(
            std::shared_ptr<IResourceLoader> loader)
        {
            m_loaderRegistry.Register<T>(
                std::move(loader)
            );
        }

        template<IsResource T>
        std::shared_ptr<T> Load(
            const std::string& filepath)
        {
            const auto typeKey =
                std::type_index(typeid(T));

            auto& resourceMap =
                m_resources[typeKey];

            const auto it =
                resourceMap.find(filepath);

            // Reutiliza recurso que já está no cache.
            if (it != resourceMap.end())
            {
                if (it->second)
                {
                    return std::static_pointer_cast<T>(
                        it->second
                    );
                }

                resourceMap.erase(it);
            }

            // Procura o loader responsável pelo tipo.
            auto loader =
                m_loaderRegistry.Get<T>();

            if (!loader)
            {
                throw std::runtime_error(
                    "No resource loader registered for requested type."
                );
            }

            // O loader cria o recurso.
            auto resource =
                loader->Load(filepath);

            if (!resource)
            {
                throw std::runtime_error(
                    "Resource loader failed to load: " + filepath
                );
            }

            auto typedResource =
                std::dynamic_pointer_cast<T>(resource);

            if (!typedResource)
            {
                throw std::runtime_error(
                    "Resource loader returned an invalid resource type."
                );
            }

            resourceMap.emplace(
                filepath,
                typedResource
            );

            return typedResource;
        }

        template<IsResource T>
        std::shared_ptr<T> Get(
            const std::string& filepath) const
        {
            const auto typeKey =
                std::type_index(typeid(T));

            const auto typeIt =
                m_resources.find(typeKey);

            if (typeIt == m_resources.end())
            {
                return nullptr;
            }

            const auto resourceIt =
                typeIt->second.find(filepath);

            if (resourceIt == typeIt->second.end())
            {
                return nullptr;
            }

            if (!resourceIt->second)
            {
                return nullptr;
            }

            return std::static_pointer_cast<T>(
                resourceIt->second
            );
        }

        void Cleanup()
        {
            for (auto& [typeKey, resourceMap] : m_resources)
            {
                for (auto it = resourceMap.begin();
                     it != resourceMap.end();)
                {
                    if (it->second.use_count() == 1)
                    {
                        it = resourceMap.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }

        void Clear()
        {
            m_resources.clear();
        }

    private:
        using ResourceMap =
            std::unordered_map<
                std::string,
                std::shared_ptr<Resource>
            >;

        std::unordered_map<
            std::type_index,
            ResourceMap
        > m_resources;

        ResourceLoaderRegistry m_loaderRegistry;
    };
}