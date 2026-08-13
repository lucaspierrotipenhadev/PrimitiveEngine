#pragma once

#include "Primitive/Renderer/IRendererAPI.hpp"

namespace primitive
{
    class TestRendererAPI final : public IRendererAPI
    {
    public:
        void Initialize() override;
        void Shutdown() override;

        void BeginFrame() override;
        void EndFrame() override;
    };
}