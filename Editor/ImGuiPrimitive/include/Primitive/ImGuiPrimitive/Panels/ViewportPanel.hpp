#pragma once

#include <glm/glm.hpp>

namespace primitive
{
    class ViewportPanel
    {
    public:
        ViewportPanel() = default;
        
        void OnRender();

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

        bool m_focused{false};
        bool m_hovered{false};
    };
}