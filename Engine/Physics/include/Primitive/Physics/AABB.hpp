#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    struct AABB
    {
        glm::vec3 min{0.0f, 0.0f, 0.0f};
        glm::vec3 max{0.0f, 0.0f, 0.0f};

        [[nodiscard]]
        glm::vec3 GetCenter() const;

        [[nodiscard]]
        glm::vec3 GetHalfExtends() const;

        [[nodiscard]]
        bool Intercects(const AABB& other) const;
    };
};