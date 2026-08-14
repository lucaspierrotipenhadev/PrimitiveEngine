#pragma once

#include <cstddef>

namespace primitive
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        VertexBuffer() = default;

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetData(
            const void* data,
            std::size_t size) = 0;
    };
}