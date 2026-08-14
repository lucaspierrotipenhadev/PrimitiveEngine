#pragma once

#include <cstdint>
#include <vector>

namespace primitive
{
    enum class ShaderDataType
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Int,
        Int2,
        Int3,
        Int4
    };

    struct VertexBufferElement
    {
        ShaderDataType type{ShaderDataType::None};
        std::uint32_t count{0};
        std::uint32_t offset{0};
        bool normalized{false};
    };

    class VertexBufferLayout
    {
    public:
        void Push(
            ShaderDataType type,
            bool normalized = false
        );

        [[nodiscard]]
        const std::vector<VertexBufferElement>&
        GetElements() const
        {
            return m_elements;
        }

        [[nodiscard]]
        std::uint32_t GetStride() const
        {
            return m_stride;
        }

    private:
        std::vector<VertexBufferElement> m_elements;
        std::uint32_t m_stride{0};
    };
}