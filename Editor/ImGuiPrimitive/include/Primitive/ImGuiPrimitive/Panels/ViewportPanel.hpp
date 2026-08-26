#pragma once

#include <glm/glm.hpp>

#include <cstdint>

namespace primitive
{
    class ViewportPanel
    {
    public:
        ViewportPanel() = default;
        
        void OnRender();
        void SetTextureID(std::uint32_t textureID);

        [[nodiscard]]
        const glm::vec2& GetSize() const;

        [[nodiscard]]
        const glm::vec2& GetPosition() const;

        [[nodiscard]]
        bool IsFocused() const;

        [[nodiscard]]
        bool IsHovered() const;

    private:
        glm::vec2 m_size{0.0f, 0.0f};
        glm::vec2 m_position{0.0f, 0.0f};

        std::uint32_t m_textureID{0};

        bool m_focused{false};
        bool m_hovered{false};
    };
}