#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    struct CollisionManifold
    {
        bool colliding{false};

        glm::vec3 normal{0.0f, 0.0f, 0.0f};

        float penetrationDepth{0.0f};
    };
};