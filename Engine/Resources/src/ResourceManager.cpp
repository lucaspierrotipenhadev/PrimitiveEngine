#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <concepts>

#include "Primitive/Resources/Resource.hpp"

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

        template<IsResource T, typename... Args>
        std::shared_ptr<T> Load(const std::string& filepath, Args&&... args)
        {
            auto typeKey = std::type_index(typeid(T));
            auto& resourceMap = m_resources[typeKey];

            auto it = resourceMap.find(filepath);
            if (it != resourceMap.end() && it->second) // Verifica se é válido
            {
                return std::static_pointer_cast<T>(it->second);
            }

            auto resource = std::make_shared<T>(filepath, std::forward<Args>(args)...);
            resourceMap[filepath] = resource;

            return resource;
        }

        template<IsResource T>
        std::shared_ptr<T> Get(const std::string& filepath) const
        {
            auto typeKey = std::type_index(typeid(T));
            auto typeIt = m_resources.find(typeKey);
            if (typeIt == m_resources.end()) return nullptr;

            auto resIt = typeIt->second.find(filepath);
            if (resIt == typeIt->second.end()) return nullptr;

            if (!resIt->second) return nullptr; // Verifica se é válido

            return std::static_pointer_cast<T>(resIt->second);
        }

        void UnloadUnused()
        {
            // Com shared_ptr, use_count() == 1 significa que só o ResourceManager tem referência
            for (auto& [typeKey, resourceMap] : m_resources)
            {
                for (auto it = resourceMap.begin(); it != resourceMap.end(); )
                {
                    if (it->second.use_count() == 1) // Só o manager tem referência
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
        // Mantendo shared_ptr
        std::unordered_map<
            std::type_index,
            std::unordered_map<std::string, std::shared_ptr<Resource>>
        > m_resources;
    };
}