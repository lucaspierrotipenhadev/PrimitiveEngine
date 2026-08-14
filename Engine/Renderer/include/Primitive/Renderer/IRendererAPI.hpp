#pragma once

#include <cstdint>

namespace primitive
{
    class IRendererAPI
    {
    public:
        virtual ~IRendererAPI() = default;

        IRendererAPI(const IRendererAPI &) = delete;
        IRendererAPI &operator=(const IRendererAPI &) = delete;

        virtual void Initialize() = 0;
        virtual void Shutdown() = 0;

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;

        virtual void Clear(float r, float g, float b, float a) = 0;
        virtual void Draw(std::uint32_t vertexCount) = 0;
        virtual void DrawIndexed(std::uint32_t indexCount) = 0;

    protected:
        IRendererAPI() = default;
    };
}