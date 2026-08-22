#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    class Camera
    {
    public:
        Camera() = default;

        explicit Camera(
            const glm::mat4& projection
        );

        [[nodiscard]]
        const glm::mat4& GetProjection() const;

        void SetProjection(
            const glm::mat4& projection
        );

    private:
        glm::mat4 m_projection{
            1.0f
        };
    };
}