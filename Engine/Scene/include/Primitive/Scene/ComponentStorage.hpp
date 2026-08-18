#pragma once

#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "Primitive/Scene/EntityID.hpp"
#include "Primitive/Scene/IComponentStorage.hpp"

namespace primitive
{
    template<typename T>
    class ComponentStorage final
        : public IComponentStorage
    {
    public:
        ComponentStorage() = default;
        ~ComponentStorage() override = default;

        template<typename... Args>
        T& Add(
            EntityID entity,
            Args&&... args)
        {
            if (Has(entity))
            {
                throw std::runtime_error(
                    "Entity already has this component."
                );
            }

            auto [it, inserted] =
                m_components.try_emplace(
                    entity,
                    std::forward<Args>(args)...
                );

            if (!inserted)
            {
                throw std::runtime_error(
                    "Failed to add component."
                );
            }

            return it->second;
        }

        void Remove(EntityID entity) override
        {
            m_components.erase(entity);
        }

        [[nodiscard]]
        bool Has(EntityID entity) const override
        {
            return m_components.contains(entity);
        }

        [[nodiscard]]
        T& Get(EntityID entity)
        {
            const auto it =
                m_components.find(entity);

            if (it == m_components.end())
            {
                throw std::runtime_error(
                    "Entity does not have this component."
                );
            }

            return it->second;
        }

        [[nodiscard]]
        const T& Get(EntityID entity) const
        {
            const auto it =
                m_components.find(entity);

            if (it == m_components.end())
            {
                throw std::runtime_error(
                    "Entity does not have this component."
                );
            }

            return it->second;
        }

        void Clear() override
        {
            m_components.clear();
        }

        [[nodiscard]]
        std::size_t Size() const
        {
            return m_components.size();
        }

    private:
        std::unordered_map<EntityID, T>
            m_components;
    };
}