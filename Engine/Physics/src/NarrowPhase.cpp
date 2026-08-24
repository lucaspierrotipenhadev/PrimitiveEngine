#include "Primitive/Physics/NarrowPhase.hpp"

#include "Primitive/Scene/Scene.hpp"

#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/BoxColliderComponent.hpp"
#include "Primitive/Scene/Components/SphereColliderComponent.hpp"

namespace primitive
{
    float CalculateSphereRadius(const TransformComponent &transform, const SphereColliderComponent &collider)
    {
        const glm::vec3 scale = glm::abs(transform.transform.GetScale());
        const float maxScale = glm::max(scale.x, glm::max(scale.y, scale.z));

        return collider.radius * maxScale;
    }

    CollisionManifold NarrowPhase::TestCollision(Scene &scene, const BroadPhasePair &pair) const
    {
        const auto firstShape = pair.first.colliderShape;
        const auto secondShape = pair.second.colliderShape;

        if (firstShape == ColliderShape::Box && secondShape == ColliderShape::Box)
        {
            return TestBoxBox(scene, pair.first, pair.second);
        }

        if (firstShape == ColliderShape::Sphere && secondShape == ColliderShape::Sphere)
        {
            return TestSphereSphere(scene, pair.first, pair.second);
        }

        if (firstShape == ColliderShape::Box && secondShape == ColliderShape::Sphere)
        {
            return TestBoxSphere(scene, pair.first, pair.second);
        }

        if (firstShape == ColliderShape::Sphere && secondShape == ColliderShape::Box)
        {
            CollisionManifold manifold = TestBoxSphere(scene, pair.second, pair.first);
            manifold.normal = -manifold.normal;
            return manifold;
        }
        return {};
    }

    CollisionManifold NarrowPhase::TestBoxBox(Scene &scene, const BroadPhaseProxy &first, const BroadPhaseProxy &second) const
    {
        (void)scene;

        const AABB &a = first.bounds;
        const AABB &b = second.bounds;

        const float overlapX = glm::min(a.max.x, b.max.x) - glm::max(a.min.x, b.min.x);
        const float overlapY = glm::min(a.max.y, b.max.y) - glm::max(a.min.y, b.min.y);
        const float overlapZ = glm::min(a.max.z, b.max.z) - glm::max(a.min.z, b.min.z);

        if (overlapX <= 0.0f || overlapY <= 0.0f || overlapZ <= 0.0f)
        {
            return {};
        }

        CollisionManifold manifold;
        manifold.colliding = true;

        const glm::vec3 centerA = a.GetCenter();
        const glm::vec3 centerB = b.GetCenter();

        if (overlapX <= overlapY && overlapX <= overlapZ)
        {
            manifold.penetrationDepth = overlapX;
            manifold.normal = glm::vec3(centerB.x >= centerA.x ? 1.0f : -1.0f, 0.0f, 0.0f);
        }
        else if (overlapY <= overlapX && overlapY <= overlapZ)
        {
            manifold.penetrationDepth = overlapY;
            manifold.normal = glm::vec3(0.0f, centerB.y >= centerA.y ? 1.0f : -1.0f, 0.0f);
        }
        else
        {
            manifold.penetrationDepth = overlapZ;
            manifold.normal = glm::vec3(0.0f, 0.0f, centerB.z >= centerA.z ? 1.0f : -1.0f);
        }
        return manifold;
    }

    CollisionManifold NarrowPhase::TestSphereSphere(Scene &scene, const BroadPhaseProxy &first, const BroadPhaseProxy &second) const
    {
        const auto &transformA = scene.GetComponent<TransformComponent>(first.entityID);
        const auto &sphereA = scene.GetComponent<SphereColliderComponent>(first.entityID);
        const auto &transformB = scene.GetComponent<TransformComponent>(second.entityID);
        const auto &sphereB = scene.GetComponent<SphereColliderComponent>(second.entityID);

        const glm::vec3 centerA = transformA.transform.GetPosition() + sphereA.collider.offset;
        const glm::vec3 centerB = transformB.transform.GetPosition() + sphereB.collider.offset;

        const float radiusA = CalculateSphereRadius(transformA, sphereA);
        const float radiusB = CalculateSphereRadius(transformB, sphereB);

        const glm::vec3 delta = centerB - centerA;

        const float distanceSquared = glm::dot(delta, delta);

        const float radiusSum = radiusA + radiusB;

        if (distanceSquared >= radiusSum * radiusSum)
        {
            return {};
        }

        const float distance = glm::sqrt(distanceSquared);

        CollisionManifold manifold;

        manifold.colliding = true;

        if (distance > 0.000001f)
        {
            manifold.normal = delta / distance;
            manifold.penetrationDepth = radiusSum - distance;
        }
        else
        {
            manifold.normal = glm::vec3(1.0f, 0.0f, 0.0f);
            manifold.penetrationDepth = radiusSum;
        }

        return manifold;
    }

    CollisionManifold NarrowPhase::TestBoxSphere(Scene &scene, const BroadPhaseProxy &first, const BroadPhaseProxy &second) const
    {
        const auto &sphereTransform = scene.GetComponent<TransformComponent>(second.entityID);
        const auto &sphere = scene.GetComponent<SphereColliderComponent>(second.entityID);

        const AABB &box = first.bounds;

        const glm::vec3 sphereCenter = sphereTransform.transform.GetPosition() + sphere.collider.offset;

        const float radius = CalculateSphereRadius(sphereTransform, sphere);

        const glm::vec3 closestPoint = glm::clamp(sphereCenter, box.min, box.max);

        const glm::vec3 delta = sphereCenter - closestPoint;

        const float distanceSquared = glm::dot(delta, delta);

        if (distanceSquared >= radius * radius)
        {
            return {};
        }

        CollisionManifold manifold;
        manifold.colliding = true;

        if (distanceSquared > 0.000001f)
        {
            const float distance = glm::sqrt(distanceSquared);
            manifold.normal = delta / distance;
            manifold.penetrationDepth = radius - distance;

            return manifold;
        }

        const float left =
            sphereCenter.x -
            box.min.x;

        const float right =
            box.max.x -
            sphereCenter.x;

        const float bottom =
            sphereCenter.y -
            box.min.y;

        const float top =
            box.max.y -
            sphereCenter.y;

        const float back =
            sphereCenter.z -
            box.min.z;

        const float front =
            box.max.z -
            sphereCenter.z;

        float minDistance =
            left;

        manifold.normal =
            glm::vec3(
                -1.0f,
                0.0f,
                0.0f);

        if (right < minDistance)
        {
            minDistance = right;

            manifold.normal =
                glm::vec3(
                    1.0f,
                    0.0f,
                    0.0f);
        }

        if (bottom < minDistance)
        {
            minDistance = bottom;

            manifold.normal =
                glm::vec3(
                    0.0f,
                    -1.0f,
                    0.0f);
        }

        if (top < minDistance)
        {
            minDistance = top;

            manifold.normal =
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f);
        }

        if (back < minDistance)
        {
            minDistance = back;

            manifold.normal =
                glm::vec3(
                    0.0f,
                    0.0f,
                    -1.0f);
        }

        if (front < minDistance)
        {
            minDistance = front;

            manifold.normal =
                glm::vec3(
                    0.0f,
                    0.0f,
                    1.0f);
        }

        manifold.penetrationDepth =
            radius +
            minDistance;

        return manifold;
    }
}