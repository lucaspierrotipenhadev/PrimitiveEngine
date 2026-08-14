#pragma once

#include <glm/glm.hpp>

#include "Primitive/Scene/Transform.hpp"

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

        [[nodiscard]]
        glm::mat4 GetView() const;

        [[nodiscard]]
        glm::mat4 GetViewProjection() const;

        void SetProjection(
            const glm::mat4& projection
        );

        [[nodiscard]]
        Transform& GetTransform();

        [[nodiscard]]
        const Transform& GetTransform() const;

    private:
        Transform m_transform;

        glm::mat4 m_projection{
            1.0f
        };
    };
}