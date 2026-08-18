#pragma once

#include <memory>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "Primitive/Scene/ComponentStorage.hpp"
#include "Primitive/Scene/EntityID.hpp"
#include "Primitive/Scene/IComponentStorage.hpp"

namespace primitive
{
    class ComponentManager
    {
    public:
        ComponentManager() = default;
        ~ComponentManager() = default;

        ComponentManager(
            const ComponentManager&) = delete;

        ComponentManager& operator=(
            const ComponentManager&) = delete;

        template<typename T, typename... Args>
        T& Add(
            EntityID entity,
            Args&&... args)
        {
            auto& storage =
                GetOrCreateStorage<T>();

            return storage.Add(
                entity,
                std::forward<Args>(args)...
            );
        }

        template<typename T>
        void Remove(EntityID entity)
        {
            auto* storage =
                FindStorage<T>();

            if (!storage)
            {
                return;
            }

            storage->Remove(entity);
        }

        template<typename T>
        [[nodiscard]]
        bool Has(EntityID entity) const
        {
            const auto* storage =
                FindStorage<T>();

            if (!storage)
            {
                return false;
            }

            return storage->Has(entity);
        }

        template<typename T>
        [[nodiscard]]
        T& Get(EntityID entity)
        {
            auto* storage =
                FindStorage<T>();

            if (!storage)
            {
                throw std::runtime_error(
                    "Component storage does not exist."
                );
            }

            return storage->Get(entity);
        }

        template<typename T>
        [[nodiscard]]
        const T& Get(EntityID entity) const
        {
            const auto* storage =
                FindStorage<T>();

            if (!storage)
            {
                throw std::runtime_error(
                    "Component storage does not exist."
                );
            }

            return storage->Get(entity);
        }

        void RemoveAll(EntityID entity)
        {
            for (auto& [type, storage] : m_storages)
            {
                storage->Remove(entity);
            }
        }

        void Clear()
        {
            m_storages.clear();
        }

    private:
        template<typename T>
        ComponentStorage<T>&
        GetOrCreateStorage()
        {
            const auto type =
                std::type_index(typeid(T));

            const auto it =
                m_storages.find(type);

            if (it != m_storages.end())
            {
                return static_cast<
                    ComponentStorage<T>&
                >(*it->second);
            }

            auto storage =
                std::make_unique<
                    ComponentStorage<T>
                >();

            auto* storagePtr =
                storage.get();

            m_storages.emplace(
                type,
                std::move(storage)
            );

            return *storagePtr;
        }

        template<typename T>
        ComponentStorage<T>*
        FindStorage()
        {
            const auto type =
                std::type_index(typeid(T));

            const auto it =
                m_storages.find(type);

            if (it == m_storages.end())
            {
                return nullptr;
            }

            return static_cast<
                ComponentStorage<T>*
            >(it->second.get());
        }

        template<typename T>
        const ComponentStorage<T>*
        FindStorage() const
        {
            const auto type =
                std::type_index(typeid(T));

            const auto it =
                m_storages.find(type);

            if (it == m_storages.end())
            {
                return nullptr;
            }

            return static_cast<
                const ComponentStorage<T>*
            >(it->second.get());
        }

    private:
        std::unordered_map<
            std::type_index,
            std::unique_ptr<IComponentStorage>
        > m_storages;
    };
}