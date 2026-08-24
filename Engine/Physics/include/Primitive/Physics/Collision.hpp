#pragma once

#include "Primitive/Physics/BroadPhase.hpp"
#include "Primitive/Physics/CollisionManifold.hpp"
#include "Primitive/Scene/EntityID.hpp"

namespace primitive
{
    struct Collision
    {
        EntityID firstEntity{NullEntity};
        EntityID secondEntity{NullEntity};
        ColliderShape firstShape{ColliderShape::Box};
        ColliderShape secondShape{ColliderShape::Box};
        CollisionManifold manifold;

        bool isTrigger{false};
    };
}