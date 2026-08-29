#pragma once

#include <utility>
#include <functional>
#include <cstdint>
#include <memory>

#include "Primitive/Scene/ComponentManager.hpp"
#include "Primitive/Scene/Entity.hpp"
#include "Primitive/Scene/EntityManager.hpp"

#include "Primitive/Physics/PhysicsWorld.hpp"
#include "Primitive/Physics/FixedTimeStep.hpp"

namespace primitive
{
    class Renderer;
    class EventBus;

    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;

        Scene(const Scene &) = delete;
        Scene &operator=(const Scene &) = delete;

        [[nodiscard]]
        Entity CreateEntity(const std::string &name = "Entity");

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

        template <typename Func>
        void ForEachEntity(Func &&function)
        {
            m_entityManager.ForEach(
                std::forward<Func>(function));
        }

        template <typename Func>
        void ForEachEntity(Func &&function) const
        {
            m_entityManager.ForEach(
                std::forward<Func>(function));
        }

        void Update(float deltaTime, EventBus &eventBus);
        void Render(Renderer &renderer);

        void SetFixedTimeStep(float fixedTimeStep);
        void AdvancePhysics(float deltaTime, EventBus &eventBus);

        [[nodiscard]]
        float GetFixedTimeStep() const;

        [[nodiscard]]
        PhysicsWorld &GetPhysicsWorld();

        [[nodiscard]]
        const PhysicsWorld &GetPhysicsWorld() const;

        [[nodiscard]]
        std::unique_ptr<Scene> Clone() const;

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
        PhysicsWorld m_physicsWorld;
        FixedTimeStep m_physicsTimeStep;

        std::uint32_t m_maxPhysicsStepsPerFrame{8};
    };
}

#include "Primitive/Scene/Entity.inl"