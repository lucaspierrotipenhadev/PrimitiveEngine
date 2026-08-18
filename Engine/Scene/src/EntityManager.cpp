#include "Primitive/Scene/EntityManager.hpp"

namespace primitive
{
    EntityID EntityManager::Create()
    {
        const EntityID entity =
            m_nextEntity++;

        m_aliveEntities.insert(entity);

        return entity;
    }

    void EntityManager::Destroy(
        EntityID entity)
    {
        m_aliveEntities.erase(entity);
    }

    bool EntityManager::IsAlive(
        EntityID entity) const
    {
        return m_aliveEntities.contains(entity);
    }

    std::size_t
    EntityManager::GetAliveCount() const
    {
        return m_aliveEntities.size();
    }

    void EntityManager::Clear()
    {
        m_aliveEntities.clear();
        m_nextEntity = 0;
    }
}