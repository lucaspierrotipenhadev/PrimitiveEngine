#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    enum class RigidBodyType
    {
        Static,
        Dynamic,
        Kinematic
    };
    
    struct RigidBodyComponent
    {
        RigidBodyType type{RigidBodyType::Dynamic};

        float mass{1.0f};

        glm::vec3 velocity{0.0f, 0.0f, 0.0f};
        glm::vec3 force{0.0f, 0.0f, 0.0f};

        bool useGravity{true};

    };
};