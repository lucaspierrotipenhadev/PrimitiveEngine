#pragma once

#include <cstdint>
#include <string>

namespace primitive
{
    enum class RendererBackend
    {
        OpenGL
    };

    struct WindowConfiguration
    {
        std::uint32_t width{1280};
        std::uint32_t height{720};

        std::string title{"Primitive Engine"};

        bool fullscreen{false};
        bool vsync{true};
    };

    struct RendererConfiguration
    {
        RendererBackend backend{
            RendererBackend::OpenGL
        };
    };

    struct PhysicsConfiguration
    {
        float fixedTimeStep{1.0f / 60.0f};
    };

    struct Configuration
    {
        WindowConfiguration window;
        RendererConfiguration renderer;
        PhysicsConfiguration physics;

        std::string assetPath{"assets"};
        std::string projectPath{"."};
    };
}