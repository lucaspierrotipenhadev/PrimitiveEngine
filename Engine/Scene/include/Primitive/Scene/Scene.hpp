#pragma once

#include <utility>
#include <functional>

#include "Primitive/Scene/ComponentManager.hpp"
#include "Primitive/Scene/Entity.hpp"
#include "Primitive/Scene/EntityManager.hpp"

namespace primitive
{
    class Renderer;
    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Scene(const Scene &) = delete;
        Scene &operator=(const Scene &) = delete;

        [[nodiscard]]
        Entity CreateEntity();

        void DestroyEntity(Entity entity);

        [[nodiscard]]
        bool IsEntityAlive(
            EntityID entity) const;

        [[nodiscard]]
        std::size_t GetEntityCount() const;

        void Clear();

        template <typename T, typename... Args>
        T &AddComponent(
            EntityID entity,
            Args &&...args)
        {
            ValidateEntity(entity);

            return m_componentManager.Add<T>(
                entity,
                std::forward<Args>(args)...);
        }

        template <typename T>
        void RemoveComponent(
            EntityID entity)
        {
            ValidateEntity(entity);

            m_componentManager.Remove<T>(
                entity);
        }

        template <typename T>
        [[nodiscard]]
        bool HasComponent(
            EntityID entity) const
        {
            if (!m_entityManager.IsAlive(entity))
            {
                return false;
            }

            return m_componentManager.Has<T>(
                entity);
        }

        template <typename T>
        [[nodiscard]]
        T &GetComponent(
            EntityID entity)
        {
            ValidateEntity(entity);

            return m_componentManager.Get<T>(
                entity);
        }

        template <typename T>
        [[nodiscard]]
        const T &GetComponent(
            EntityID entity) const
        {
            ValidateEntity(entity);

            return m_componentManager.Get<T>(
                entity);
        }

        template <typename... Components, typename Func>
        void ForEach(Func &&function)
        {
            m_entityManager.ForEach(
                [this, &function](EntityID entity)
                {
                    if (!HasAllComponents<Components...>(
                            entity))
                    {
                        return;
                    }

                    std::invoke(
                        function,
                        entity,
                        m_componentManager
                            .Get<Components>(
                                entity)...);
                });
        }

        void Update(float deltaTime);
        void Render(Renderer& renderer);

    private:
        void ValidateEntity(
            EntityID entity) const;

        template <typename T>
        [[nodiscard]]
        bool HasAllComponents(
            EntityID entity) const
        {
            return m_componentManager.Has<T>(
                entity);
        }

        template <
            typename T,
            typename U,
            typename... Rest>
        [[nodiscard]]
        bool HasAllComponents(
            EntityID entity) const
        {
            if (!m_componentManager.Has<T>(
                    entity))
            {
                return false;
            }

            return HasAllComponents<
                U,
                Rest...>(entity);
        }

    private:
        EntityManager m_entityManager;
        ComponentManager m_componentManager;
    };
}

#include "Primitive/Scene/Entity.inl"