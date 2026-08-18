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

        void Clear();

    private:
        EntityID m_nextEntity{0};

        std::unordered_set<EntityID>
            m_aliveEntities;
    };
}