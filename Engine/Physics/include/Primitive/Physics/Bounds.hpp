#pragma once

namespace primitive
{
    struct AABB;
    struct TransformComponent;
    struct BoxColliderComponent;
    struct SphereColliderComponent;

    [[nodiscard]]
    AABB CalculateAABB(const TransformComponent& transform, const BoxColliderComponent& collider);

    [[nodiscard]]
    AABB CalculateAABB(const TransformComponent& transformComponents, const SphereColliderComponent& collider);
};