#include "Primitive/Scene/Entity.hpp"

#include "Primitive/Scene/Scene.hpp"

namespace primitive
{
    Entity::Entity(
        EntityID id,
        Scene* scene)
        : m_id(id),
          m_scene(scene)
    {
    }

    EntityID Entity::GetID() const
    {
        return m_id;
    }

    bool Entity::IsValid() const
    {
        if (!m_scene)
        {
            return false;
        }

        if (m_id == NullEntity)
        {
            return false;
        }

        return m_scene->IsEntityAlive(
            m_id
        );
    }

    Entity::operator bool() const
    {
        return IsValid();
    }
}