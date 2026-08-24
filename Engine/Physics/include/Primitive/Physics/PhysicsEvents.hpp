#pragma once

#include "Primitive/Physics/Collision.hpp"

namespace primitive
{
    struct CollisionEnterEvent
    {
        Collision collision;
    };

    struct CollisionStayEvent
    {
        Collision collision;
    };
    
    struct CollisionExitEvent
    {
        EntityID firstEntity{NullEntity};
        EntityID secondEntity{NullEntity};
    };

    struct TriggerEnterEvent
    {
        Collision collision;
    };

    struct TriggerStayEvent
    {
        Collision collision;
    };

    struct TriggerExitEvent
    {
        EntityID firstEntity{NullEntity};
        EntityID secondEntity{NullEntity};
    };
};