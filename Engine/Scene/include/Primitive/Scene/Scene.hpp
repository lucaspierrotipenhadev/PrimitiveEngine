#pragma once

#include <utility>

#include "Primitive/Scene/ComponentManager.hpp"
#include "Primitive/Scene/Entity.hpp"
#include "Primitive/Scene/EntityManager.hpp"

namespace primitive
{
    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Scene(const Scene&) = delete;
        Scene& operator=(const Scene&) = delete;

        [[nodiscard]]
        Entity CreateEntity();

        void DestroyEntity(Entity entity);

        [[nodiscard]]
        bool IsEntityAlive(
            EntityID entity
        ) const;

        [[nodiscard]]
        std::size_t GetEntityCount() const;

        void Clear();

        template<typename T, typename... Args>
        T& AddComponent(
            EntityID entity,
            Args&&... args)
        {
            ValidateEntity(entity);

            return m_componentManager.Add<T>(
                entity,
                std::forward<Args>(args)...
            );
        }

        template<typename T>
        void RemoveComponent(
            EntityID entity)
        {
            ValidateEntity(entity);

            m_componentManager.Remove<T>(
                entity
            );
        }

        template<typename T>
        [[nodiscard]]
        bool HasComponent(
            EntityID entity) const
        {
            if (!m_entityManager.IsAlive(entity))
            {
                return false;
            }

            return m_componentManager.Has<T>(
                entity
            );
        }

        template<typename T>
        [[nodiscard]]
        T& GetComponent(
            EntityID entity)
        {
            ValidateEntity(entity);

            return m_componentManager.Get<T>(
                entity
            );
        }

        template<typename T>
        [[nodiscard]]
        const T& GetComponent(
            EntityID entity) const
        {
            ValidateEntity(entity);

            return m_componentManager.Get<T>(
                entity
            );
        }

    private:
        void ValidateEntity(
            EntityID entity
        ) const;

    private:
        EntityManager m_entityManager;
        ComponentManager m_componentManager;
    };
}

#include "Primitive/Scene/Entity.inl"