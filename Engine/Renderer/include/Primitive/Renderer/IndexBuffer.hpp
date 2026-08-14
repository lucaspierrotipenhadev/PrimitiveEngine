#pragma once

#include <cstdint>

namespace primitive
{
    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() = default;

        IndexBuffer() = default;

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        [[nodiscard]]
        virtual std::uint32_t GetCount() const = 0;
    };
}