#pragma once

#include <cstddef>
#include <unordered_set>

#include "Primitive/Scene/EntityID.hpp"

namespace primitive
{
    class EntityManager
    {
    public:
        EntityManager() = default;
        ~EntityManager() = default;

        EntityManager(const EntityManager&) = delete;
        EntityManager& operator=(const EntityManager&) = delete;

        [[nodiscard]]
        EntityID Create();

        void Destroy(EntityID entity);

        [[nodiscard]]
        bool IsAlive(EntityID entity) const;

        [[nodiscard]]
        std::size_t GetAliveCount() const;

        template<typename Func>
        void ForEach(Func&& function) const
        {
            for (const EntityID entity : m_aliveEntities)
            {
                std::forward<Func>(function)(
                    entity
                );
            }
        }

        void Clear();

    private:
        EntityID m_nextEntity{0};

        std::unordered_set<EntityID>
            m_aliveEntities;
    };
}