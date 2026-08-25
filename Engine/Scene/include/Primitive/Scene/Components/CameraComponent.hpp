#pragma once

#include <utility>

#include <glm/gtc/matrix_transform.hpp>

#include "Primitive/Renderer/Camera.hpp"

namespace primitive
{
    enum class CameraProjectionType
    {
        Perspective,
        Orthographic
    };

    struct CameraComponent
    {
        CameraComponent() = default;

        explicit CameraComponent(
            Camera cameraValue,
            bool isPrimary = false)
            : camera(std::move(cameraValue)),
              primary(isPrimary)
        {
        }

        void UppdateProjection(float aspectRatio)
        {
            switch(projectionType)
            {
            case CameraProjectionType::Perspective:
            {
                camera.SetProjection(glm::perspective(glm::radians(perspectiveFov), aspectRatio, perspectiveNear, perspectiveFar));
                break;
            }
            
            case CameraProjectionType::Orthographic:
            {
                const float halfHeight = orthographicSize * 0.5f;
                const float halfWight = halfHeight * aspectRatio;
                camera.SetProjection(glm::ortho(-halfWight, halfWight, -halfHeight, halfHeight, orthographicNear, orthographicFar));
                break;
            }
            }
        }

        Camera camera;
        CameraProjectionType projectionType{CameraProjectionType::Perspective};

        float perspectiveFov{45.0f};
        float perspectiveNear{0.1f};
        float perspectiveFar{100.0f};

        float orthographicSize{10.0f};
        float orthographicNear{-1.0f};
        float orthographicFar{1.0f};

        bool primary{false};
    };
}