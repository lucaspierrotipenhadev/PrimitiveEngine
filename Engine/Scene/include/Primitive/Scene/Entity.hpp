#pragma once

#include "Primitive/Scene/EntityID.hpp"

namespace primitive
{
    class Scene;

    class Entity
    {
    public:
        Entity() = default;

        Entity(
            EntityID id,
            Scene* scene
        );

        [[nodiscard]]
        EntityID GetID() const;

        [[nodiscard]]
        bool IsValid() const;

        explicit operator bool() const;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args);

        template<typename T>
        void RemoveComponent();

        template<typename T>
        [[nodiscard]]
        bool HasComponent() const;

        template<typename T>
        [[nodiscard]]
        T& GetComponent();

        template<typename T>
        [[nodiscard]]
        const T& GetComponent() const;

    private:
        EntityID m_id{NullEntity};
        Scene* m_scene{nullptr};
    };
}