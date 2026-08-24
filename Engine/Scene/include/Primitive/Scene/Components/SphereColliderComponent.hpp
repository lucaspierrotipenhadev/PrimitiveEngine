#pragma once

#include <glm/glm.hpp>

#include "Primitive/Physics/Collider.hpp"

namespace primitive
{
    struct SphereColliderComponent
    {
        Collider collider;
        float radius{0.5f};
    };
};