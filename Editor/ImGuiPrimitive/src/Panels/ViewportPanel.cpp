#include "Primitive/ImGuiPrimitive/Panels/ViewportPanel.hpp"

#include <imgui.h>

namespace primitive
{
    void ViewportPanel::OnRender(const std::function<void()> &overlayCallback)
    {
        ImGui::Begin("Viewport");

        m_focused = ImGui::IsWindowFocused();

        m_hovered = ImGui::IsWindowHovered();

        const ImVec2 availableRegion = ImGui::GetContentRegionAvail();

        m_size = glm::vec2{availableRegion.x, availableRegion.y};

        const ImVec2 windowPosition = ImGui::GetWindowPos();
        const ImVec2 contentMin = ImGui::GetWindowContentRegionMin();

        m_position = glm::vec2{
            windowPosition.x + contentMin.x,
            windowPosition.y + contentMin.y};

        ImGui::TextDisabled("Scene Viewport");
        ImGui::Text("Size: %.0f x %.0f", m_size.x, m_size.y);
        ImGui::Text("Focused: %s", m_focused ? "Yes" : "No");
        ImGui::Text("Hovered: %s", m_hovered ? "Yes" : "No");

        if (m_textureID != 0 &&
            m_size.x > 0.0f &&
            m_size.y > 0.0f)
        {
            ImGui::Image(
                static_cast<ImTextureID>(
                    m_textureID),
                ImVec2{
                    m_size.x,
                    m_size.y},
                ImVec2{0.0f, 1.0f},
                ImVec2{1.0f, 0.0f});
        }

        if (overlayCallback)
        {
            overlayCallback();
        }

        ImGui::End();
    }

    const glm::vec2 &
    ViewportPanel::GetSize() const
    {
        return m_size;
    }

    const glm::vec2 &
    ViewportPanel::GetPosition() const
    {
        return m_position;
    }

    bool ViewportPanel::IsFocused() const
    {
        return m_focused;
    }

    bool ViewportPanel::IsHovered() const
    {
        return m_hovered;
    }

    void ViewportPanel::SetTextureID(std::uint32_t textureID)
    {
        m_textureID = textureID;
    }
}