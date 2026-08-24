#pragma once

#include "Primitive/Physics/BroadPhase.hpp"
#include "Primitive/Physics/CollisionManifold.hpp"

namespace primitive
{
    class Scene;

    class NarrowPhase
    {
    public:
        [[nodiscard]]
        CollisionManifold TestCollision(Scene& scene, const BroadPhasePair& pair) const;

    private:
        [[nodiscard]]
        CollisionManifold TestBoxBox(Scene& scene, const BroadPhaseProxy& first, const BroadPhaseProxy& second) const;

        [[nodiscard]]
        CollisionManifold TestSphereSphere(Scene& scene, const BroadPhaseProxy& first, const BroadPhaseProxy& second) const;

        [[nodiscard]]
        CollisionManifold TestBoxSphere(Scene& scene, const BroadPhaseProxy& first, const BroadPhaseProxy& second) const;
    };
};