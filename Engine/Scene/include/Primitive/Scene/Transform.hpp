#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    class Transform
    {
    public:
        Transform() = default;

        [[nodiscard]]
        glm::mat4 GetMatrix() const;

        [[nodiscard]]
        const glm::vec3& GetPosition() const;

        [[nodiscard]]
        const glm::vec3& GetRotation() const;

        [[nodiscard]]
        const glm::vec3& GetScale() const;

        void SetPosition(
            const glm::vec3& position
        );

        void SetRotation(
            const glm::vec3& rotation
        );

        void SetScale(
            const glm::vec3& scale
        );

        void Translate(
            const glm::vec3& offset
        );

        void Rotate(
            const glm::vec3& rotation
        );

    private:
        glm::vec3 m_position{
            0.0f,
            0.0f,
            0.0f
        };

        // Em graus por enquanto.
        glm::vec3 m_rotation{
            0.0f,
            0.0f,
            0.0f
        };

        glm::vec3 m_scale{
            1.0f,
            1.0f,
            1.0f
        };
    };
}