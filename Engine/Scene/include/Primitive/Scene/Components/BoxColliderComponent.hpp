#pragma once

#include <glm/glm.hpp>

#include "Primitive/Physics/Collider.hpp"

namespace primitive
{
    struct BoxColliderComponent
    {
        Collider collider;

        glm::vec3 halfExtends{0.5f, 0.5f, 0.5f};
    };
};