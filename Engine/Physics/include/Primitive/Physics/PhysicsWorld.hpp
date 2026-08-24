#pragma once

#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>

#include "Primitive/Physics/BroadPhase.hpp"
#include "Primitive/Physics/NarrowPhase.hpp"
#include "Primitive/Physics/Collision.hpp"
#include "Primitive/Physics/CollisionPair.hpp"

namespace primitive
{
    class Scene;
    class EventBus;

    class PhysicsWorld
    {
    public:
        PhysicsWorld() = default;
        ~PhysicsWorld() = default;

        PhysicsWorld(const PhysicsWorld &) = delete;
        PhysicsWorld &operator=(const PhysicsWorld &) = delete;

        void Step(Scene &scene, float deltaTime);
        void Clear();
        void SetGravity(const glm::vec3 &gravity);
        void PublishCollisionEvents(EventBus &event);
        void ResolveCollisions(Scene &scene);
        void ResolveCollision(Scene &scene, const Collision &collision);

        [[nodiscard]]
        const glm::vec3 &GetGravity() const;

        [[nodiscard]]
        const std::vector<Collision> &GetCollisions() const;

    private:
        glm::vec3 m_gravity{0.0f, -9.81f, 0.0f};

        std::vector<Collision> m_collisions;

        void DetectCollisions(Scene &scene, const std::vector<BroadPhasePair> &candidatePairs);

        [[nodiscard]]
        std::vector<BroadPhaseProxy> BuildPhaseProxies(Scene &scene) const;

        void IntegrateRigidbodies(Scene &scene, float deltaTime);

        [[nodiscard]]
        bool IsTrigger(Scene &scene, const BroadPhaseProxy &proxy) const;

        BroadPhase m_broadPhase;
        NarrowPhase m_narrowPhase;

        using CollisionMap = std::unordered_map<CollisionPair, Collision, CollisionPairHash>;

        CollisionMap m_previousCollisions;
        CollisionMap m_currentCollisions;
    };
}