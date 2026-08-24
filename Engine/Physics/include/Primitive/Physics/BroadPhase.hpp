#pragma once

#include <vector>

#include "Primitive/Physics/AABB.hpp"
#include "Primitive/Scene/EntityID.hpp"

namespace primitive
{
    enum class ColliderShape
    {
        Box,
        Sphere
    };

    struct BroadPhaseProxy
    {
        EntityID entityID{NullEntity};
        ColliderShape colliderShape{ColliderShape::Box};
        AABB bounds;
    };

    struct BroadPhasePair
    {
        BroadPhaseProxy first;
        BroadPhaseProxy second;
    };

    class BroadPhase
    {
    public:
        [[nodiscard]]
        std::vector<BroadPhasePair> ComputePairs(const std::vector<BroadPhaseProxy>& proxies) const;
    };
};