#include "Primitive/Renderer/Camera.hpp"

namespace primitive
{
    Camera::Camera(
        const glm::mat4& projection)
        : m_projection(projection)
    {
    }

    const glm::mat4&
    Camera::GetProjection() const
    {
        return m_projection;
    }

    void Camera::SetProjection(
        const glm::mat4& projection)
    {
        m_projection = projection;
    }
}