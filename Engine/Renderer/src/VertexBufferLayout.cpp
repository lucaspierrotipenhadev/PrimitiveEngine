#include "Primitive/Renderer/VertexBufferLayout.hpp"

#include <stdexcept>

namespace primitive
{
    namespace
    {
        std::uint32_t ShaderDataTypeSize(
            ShaderDataType type)
        {
            switch (type)
            {
            case ShaderDataType::Float:
                return 4;

            case ShaderDataType::Float2:
                return 4 * 2;

            case ShaderDataType::Float3:
                return 4 * 3;

            case ShaderDataType::Float4:
                return 4 * 4;

            case ShaderDataType::Int:
                return 4;

            case ShaderDataType::Int2:
                return 4 * 2;

            case ShaderDataType::Int3:
                return 4 * 3;

            case ShaderDataType::Int4:
                return 4 * 4;

            default:
                throw std::runtime_error(
                    "Unsupported ShaderDataType."
                );
            }
        }

        std::uint32_t ShaderDataTypeCount(
            ShaderDataType type)
        {
            switch (type)
            {
            case ShaderDataType::Float:
            case ShaderDataType::Int:
                return 1;

            case ShaderDataType::Float2:
            case ShaderDataType::Int2:
                return 2;

            case ShaderDataType::Float3:
            case ShaderDataType::Int3:
                return 3;

            case ShaderDataType::Float4:
            case ShaderDataType::Int4:
                return 4;

            default:
                throw std::runtime_error(
                    "Unsupported ShaderDataType."
                );
            }
        }
    }

    void VertexBufferLayout::Push(
        ShaderDataType type,
        bool normalized)
    {
        VertexBufferElement element;

        element.type = type;
        element.count =
            ShaderDataTypeCount(type);

        element.offset =
            m_stride;

        element.normalized =
            normalized;

        m_elements.push_back(element);

        m_stride +=
            ShaderDataTypeSize(type);
    }
}