#include "Primitive/Scene/Scene.hpp"

#include <stdexcept>

namespace primitive
{
    Entity Scene::CreateEntity()
    {
        const EntityID id =
            m_entityManager.Create();

        return Entity{
            id,
            this
        };
    }

    void Scene::DestroyEntity(
        Entity entity)
    {
        const EntityID id =
            entity.GetID();

        ValidateEntity(id);

        m_componentManager.RemoveAll(id);

        m_entityManager.Destroy(id);
    }

    bool Scene::IsEntityAlive(
        EntityID entity) const
    {
        return m_entityManager.IsAlive(
            entity
        );
    }

    std::size_t
    Scene::GetEntityCount() const
    {
        return m_entityManager
            .GetAliveCount();
    }

    void Scene::Clear()
    {
        m_componentManager.Clear();
        m_entityManager.Clear();
    }

    void Scene::ValidateEntity(
        EntityID entity) const
    {
        if (entity == NullEntity)
        {
            throw std::runtime_error(
                "Invalid entity."
            );
        }

        if (!m_entityManager.IsAlive(entity))
        {
            throw std::runtime_error(
                "Entity is not alive."
            );
        }
    }
}