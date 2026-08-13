#pragma once

#include "Primitive/Renderer/IRendererAPI.hpp"

namespace primitive
{
    class OpenGLRenderer final: public IRendererAPI
    {
        public:
            OpenGLRenderer() = default;
            ~OpenGLRenderer() override = default;

            void Initialize() override;
            void Shutdown() override;

            void BeginFrame() override;
            void EndFrame() override;

            void Clear(float r, float g, float b, float a) override;
    };
}