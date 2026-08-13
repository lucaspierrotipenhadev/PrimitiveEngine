#pragma once

#include <memory>

#include "Primitive/Renderer/IRendererAPI.hpp"

namespace primitive
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        void Initialize();
        void Shutdown();

        void BeginFrame();
        void EndFrame();

        void Clear(float r, float g, float b, float a);

    private:
        std::unique_ptr<IRendererAPI> m_api;
    };
}