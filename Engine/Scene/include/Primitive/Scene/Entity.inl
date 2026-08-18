#pragma once

#include <stdexcept>
#include <utility>

#include "Primitive/Scene/Entity.hpp"

namespace primitive
{
    template<typename T, typename... Args>
    T& Entity::AddComponent(
        Args&&... args)
    {
        if (!IsValid())
        {
            throw std::runtime_error(
                "Cannot add component to invalid entity."
            );
        }

        return m_scene->AddComponent<T>(
            m_id,
            std::forward<Args>(args)...
        );
    }

    template<typename T>
    void Entity::RemoveComponent()
    {
        if (!IsValid())
        {
            throw std::runtime_error(
                "Cannot remove component from invalid entity."
            );
        }

        m_scene->RemoveComponent<T>(
            m_id
        );
    }

    template<typename T>
    bool Entity::HasComponent() const
    {
        if (!IsValid())
        {
            return false;
        }

        return m_scene->HasComponent<T>(
            m_id
        );
    }

    template<typename T>
    T& Entity::GetComponent()
    {
        if (!IsValid())
        {
            throw std::runtime_error(
                "Cannot get component from invalid entity."
            );
        }

        return m_scene->GetComponent<T>(
            m_id
        );
    }

    template<typename T>
    const T& Entity::GetComponent() const
    {
        if (!IsValid())
        {
            throw std::runtime_error(
                "Cannot get component from invalid entity."
            );
        }

        return m_scene->GetComponent<T>(
            m_id
        );
    }
}