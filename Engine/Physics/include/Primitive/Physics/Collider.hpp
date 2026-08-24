#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    struct Collider
    {
        glm::vec3 offset{0.0f, 0.0f, 0.0f};

        float friction{0.5f};
        float restitution{0.0f};
        
        bool isTrigger{false};
        bool enabled{true};
    };
};