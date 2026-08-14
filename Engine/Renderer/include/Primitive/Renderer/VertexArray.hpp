#pragma once

#include "Primitive/Renderer/VertexBuffer.hpp"
#include "Primitive/Renderer/VertexBufferLayout.hpp"

namespace primitive
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        VertexArray() = default;

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(
            const VertexArray&) = delete;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(
            const VertexBuffer& vertexBuffer,
            const VertexBufferLayout& layout
        ) = 0;
    };
}