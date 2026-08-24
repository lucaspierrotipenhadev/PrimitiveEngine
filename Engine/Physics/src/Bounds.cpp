#include "Primitive/Physics/Bounds.hpp"

#include <glm/common.hpp>

#include "Primitive/Physics/AABB.hpp"

#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/BoxColliderComponent.hpp"
#include "Primitive/Scene/Components/SphereColliderComponent.hpp"

namespace primitive
{
    AABB CalculateAABB(const TransformComponent& transformComponent, const BoxColliderComponent& collider) 
    {
        const auto& transform = transformComponent.transform;

        const glm::vec3 scale = glm::abs(transform.GetScale());
        const glm::vec3 center = transform.GetPosition() + collider.collider.offset;
        const glm::vec3 halfExtends = collider.halfExtends * scale;

        return AABB{center - halfExtends, center + halfExtends};
    }

    AABB CalculateAABB(const TransformComponent& transformComponent, const SphereColliderComponent& collider) 
    {
        const auto& transform = transformComponent.transform;

        const glm::vec3 scale = glm::abs(transform.GetScale());

        const float maxScale = glm::max(scale.x, glm::max(scale.y, scale.z));
        const float radius = collider.radius * maxScale;

        const glm::vec3 center = transform.GetPosition() + collider.collider.offset;
        const glm::vec3 extends{radius};

        return AABB{center - extends, center + extends};
    }
};