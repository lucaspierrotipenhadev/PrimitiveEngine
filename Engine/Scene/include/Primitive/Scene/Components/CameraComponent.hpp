#pragma once

#include <utility>

#include "Primitive/Renderer/Camera.hpp"

namespace primitive
{
    struct CameraComponent
    {
        Camera camera;

        bool primary{false};

        CameraComponent() = default;

        explicit CameraComponent(
            Camera cameraValue,
            bool isPrimary = false)
            : camera(std::move(cameraValue)),
              primary(isPrimary)
        {
        }
    };
}