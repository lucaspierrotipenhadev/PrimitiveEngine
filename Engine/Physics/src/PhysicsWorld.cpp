#include "Primitive/Physics/PhysicsWorld.hpp"

#include "Primitive/Physics/Bounds.hpp"
#include "Primitive/Physics/PhysicsEvents.hpp"

#include "Primitive/Core/EventBus.hpp"

#include "Primitive/Scene/Scene.hpp"
#include "Primitive/Scene/Components/RigidBodyComponent.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/SphereColliderComponent.hpp"
#include "Primitive/Scene/Components/BoxColliderComponent.hpp"

namespace primitive
{
    float GetInverseMass(const RigidBodyComponent *rigidyBody)
    {
        if (!rigidyBody)
        {
            return 0.0f;
        }
        if (rigidyBody->type != RigidBodyType::Dynamic)
        {
            return 0.0f;
        }
        if (rigidyBody->mass <= 0.0f)
        {
            return 0.0f;
        }

        return 1.0f / rigidyBody->mass;
    }

    RigidBodyComponent *GetRigidBody(Scene &scene, EntityID entity)
    {
        if (!scene.HasComponent<RigidBodyComponent>(entity))
        {
            return nullptr;
        }

        return &scene.GetComponent<RigidBodyComponent>(entity);
    }

    float GetRestitution(Scene &scene, EntityID entity, ColliderShape shape)
    {
        switch (shape)
        {
        case ColliderShape::Box:
            return scene
                .GetComponent<BoxColliderComponent>(entity)
                .collider
                .restitution;

        case ColliderShape::Sphere:
            return scene
                .GetComponent<SphereColliderComponent>(entity)
                .collider
                .restitution;
        }

        return 0.0f;
    }

    void PhysicsWorld::Step(Scene &scene, float deltaTime)
    {
        m_collisions.clear();
        m_currentCollisions.clear();

        if (deltaTime <= 0.0f)
        {
            return;
        }

        IntegrateRigidbodies(scene, deltaTime);

        const auto proxies = BuildPhaseProxies(scene);
        const auto candidatePairs = m_broadPhase.ComputePairs(proxies);

        DetectCollisions(scene, candidatePairs);
        ResolveCollisions(scene);
    }

    void PhysicsWorld::Clear()
    {
        m_collisions.clear();
        m_currentCollisions.clear();
        m_previousCollisions.clear();
    }

    void PhysicsWorld::SetGravity(const glm::vec3 &gravity)
    {
        m_gravity = gravity;
    }

    const glm::vec3 &PhysicsWorld::GetGravity() const
    {
        return m_gravity;
    }

    std::vector<BroadPhaseProxy> PhysicsWorld::BuildPhaseProxies(Scene &scene) const
    {
        std::vector<BroadPhaseProxy> proxies;

        scene.ForEach<TransformComponent, BoxColliderComponent>(
            [&proxies](
                EntityID entity,
                TransformComponent &transform,
                BoxColliderComponent &collider)
            {
                if (!collider.collider.enabled)
                {
                    return;
                }

                proxies.push_back(BroadPhaseProxy{entity, ColliderShape::Box, CalculateAABB(transform, collider)});
            });

        scene.ForEach<TransformComponent, SphereColliderComponent>(
            [&proxies](
                EntityID entity,
                TransformComponent &transform,
                SphereColliderComponent &collider)
            {
                if (!collider.collider.enabled)
                {
                    return;
                }

                proxies.push_back(BroadPhaseProxy{entity, ColliderShape::Sphere, CalculateAABB(transform, collider)});
            });

        return proxies;
    }

    void PhysicsWorld::IntegrateRigidbodies(Scene &scene, float deltaTime)
    {
        scene.ForEach<TransformComponent, RigidBodyComponent>(
            [this, deltaTime](
                EntityID entity,
                TransformComponent &transform,
                RigidBodyComponent &rigidbody)
            {
                (void)entity;

                if (rigidbody.type != RigidBodyType::Dynamic)
                {
                    rigidbody.force = glm::vec3{0.0f};
                    return;
                }

                if (rigidbody.mass <= 0.0f)
                {
                    return;
                }

                glm::vec3 totalForce = rigidbody.force;

                if (rigidbody.useGravity)
                {
                    totalForce += m_gravity * rigidbody.mass;
                }

                const glm::vec3 acceleration = totalForce / rigidbody.mass;

                rigidbody.velocity += acceleration * deltaTime;

                transform.transform.Translate(rigidbody.velocity * deltaTime);

                rigidbody.force = glm::vec3{0.0f};
            });
    }

    bool PhysicsWorld::IsTrigger(Scene &scene, const BroadPhaseProxy &proxy) const
    {
        switch (proxy.colliderShape)
        {
        case ColliderShape::Box:
            return scene.GetComponent<BoxColliderComponent>(proxy.entityID).collider.isTrigger;

        case ColliderShape::Sphere:
            return scene.GetComponent<SphereColliderComponent>(proxy.entityID).collider.isTrigger;
        }
        return false;
    }

    const std::vector<Collision> &PhysicsWorld::GetCollisions() const
    {
        return m_collisions;
    }

    void PhysicsWorld::DetectCollisions(Scene &scene, const std::vector<BroadPhasePair> &candidatePairs)
    {
        for (const auto &pair : candidatePairs)
        {
            const CollisionManifold manifold = m_narrowPhase.TestCollision(scene, pair);

            if (!manifold.colliding)
            {
                continue;
            }

            const bool firstTrigger = IsTrigger(scene, pair.first);
            const bool secondTrigger = IsTrigger(scene, pair.second);

            Collision collision{
                pair.first.entityID,
                pair.second.entityID,
                pair.first.colliderShape,
                pair.second.colliderShape,
                manifold,
                firstTrigger || secondTrigger};

            m_collisions.push_back(collision);

            const CollisionPair key = CollisionPair::Create(collision.firstEntity, collision.secondEntity);
            m_currentCollisions.insert_or_assign(key, collision);
        }
    }

    void PhysicsWorld::PublishCollisionEvents(
        EventBus &eventBus)
    {
        for (
            const auto &[pair, collision] :
            m_currentCollisions)
        {
            const auto previous =
                m_previousCollisions.find(
                    pair);

            if (
                previous ==
                m_previousCollisions.end())
            {
                if (collision.isTrigger)
                {
                    eventBus.Publish(
                        TriggerEnterEvent{
                            collision});
                }
                else
                {
                    eventBus.Publish(
                        CollisionEnterEvent{
                            collision});
                }

                continue;
            }

            if (collision.isTrigger)
            {
                eventBus.Publish(
                    TriggerStayEvent{
                        collision});
            }
            else
            {
                eventBus.Publish(
                    CollisionStayEvent{
                        collision});
            }
        }

        for (
            const auto &[pair, collision] :
            m_previousCollisions)
        {
            if (
                m_currentCollisions.contains(
                    pair))
            {
                continue;
            }

            if (collision.isTrigger)
            {
                eventBus.Publish(
                    TriggerExitEvent{
                        pair.first,
                        pair.second});
            }
            else
            {
                eventBus.Publish(
                    CollisionExitEvent{
                        pair.first,
                        pair.second});
            }
        }

        m_previousCollisions =
            m_currentCollisions;
    }

    void PhysicsWorld::ResolveCollisions(Scene &scene)
    {
        for (const Collision &collision : m_collisions)
        {
            if (collision.isTrigger)
            {
                continue;
            }

            ResolveCollision(scene, collision);
        }
    }

    void PhysicsWorld::ResolveCollision(Scene &scene, const Collision &collision)
    {
        auto &transformA = scene.GetComponent<TransformComponent>(collision.firstEntity);
        auto &transformB = scene.GetComponent<TransformComponent>(collision.secondEntity);

        RigidBodyComponent* rigidbodyA = GetRigidBody(scene, collision.firstEntity);
        RigidBodyComponent* rigidbodyB = GetRigidBody(scene, collision.secondEntity);

        const float inverseMassA =
            GetInverseMass(
                rigidbodyA);

        const float inverseMassB =
            GetInverseMass(
                rigidbodyB);

        const float inverseMassSum =
            inverseMassA +
            inverseMassB;

        if (inverseMassSum <= 0.0f)
        {
            return;
        }

        constexpr float penetrationSlop =
            0.001f;

        constexpr float correctionPercent =
            0.8f;

        const float penetration =
            glm::max(
                collision
                        .manifold
                        .penetrationDepth -
                    penetrationSlop,
                0.0f);

        const glm::vec3 correction =
            collision.manifold.normal *
            penetration *
            correctionPercent;

        if (inverseMassA > 0.0f)
        {
            transformA
                .transform
                .Translate(
                    -correction *
                    (inverseMassA /
                     inverseMassSum));
        }

        if (inverseMassB > 0.0f)
        {
            transformB
                .transform
                .Translate(
                    correction *
                    (inverseMassB /
                     inverseMassSum));
        }

        const glm::vec3 velocityA =
            rigidbodyA
                ? rigidbodyA->velocity
                : glm::vec3{0.0f};

        const glm::vec3 velocityB =
            rigidbodyB
                ? rigidbodyB->velocity
                : glm::vec3{0.0f};

        const glm::vec3 relativeVelocity =
            velocityB -
            velocityA;

        const float velocityAlongNormal =
            glm::dot(
                relativeVelocity,
                collision.manifold.normal);

        if (velocityAlongNormal > 0.0f)
        {
            return;
        }

        const float restitutionA =
            GetRestitution(
                scene,
                collision.firstEntity,
                collision.firstShape);

        const float restitutionB =
            GetRestitution(
                scene,
                collision.secondEntity,
                collision.secondShape);

        const float restitution =
            glm::min(
                restitutionA,
                restitutionB);

        const float impulseMagnitude =
            -(
                1.0f +
                restitution) *
            velocityAlongNormal /
            inverseMassSum;

        const glm::vec3 impulse =
            collision.manifold.normal *
            impulseMagnitude;

        if (rigidbodyA)
        {
            rigidbodyA->velocity -=
                impulse *
                inverseMassA;
        }

        if (rigidbodyB)
        {
            rigidbodyB->velocity +=
                impulse *
                inverseMassB;
        }
    }
}