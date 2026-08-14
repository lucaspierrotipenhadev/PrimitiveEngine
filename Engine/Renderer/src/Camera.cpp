#include "Primitive/Renderer/Camera.hpp"

#include <glm/gtc/matrix_inverse.hpp>

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

    glm::mat4 Camera::GetView() const
    {
        return glm::inverse(
            m_transform.GetMatrix()
        );
    }

    glm::mat4
    Camera::GetViewProjection() const
    {
        return
            m_projection *
            GetView();
    }

    void Camera::SetProjection(
        const glm::mat4& projection)
    {
        m_projection = projection;
    }

    Transform&
    Camera::GetTransform()
    {
        return m_transform;
    }

    const Transform&
    Camera::GetTransform() const
    {
        return m_transform;
    }
}