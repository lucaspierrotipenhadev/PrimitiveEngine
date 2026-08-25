#include "Primitive/ImGuiPrimitive/EditorLayer.hpp"

#include "Primitive/Core/Engine.hpp"

#include <imgui.h>

namespace primitive
{
    void EditorLayer::OnAttach(
        Engine &engine)
    {
        m_engine = &engine;
        m_hierarchyPanel.SetScene(engine.GetActiveScene());
        m_hierarchyPanel.SetSelectionContext(&m_selectedEntity);
        m_inspectorPanel.SetSelectionContext(&m_selectedEntity);
    }

    void EditorLayer::OnDetach()
    {
        m_inspectorPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetScene(nullptr);
        m_engine = nullptr;
    }

    void EditorLayer::OnUpdate(
        float deltaTime)
    {
        (void)deltaTime;
    }

    void EditorLayer::OnRender()
    {
        constexpr ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        const ImGuiID dockspaceID = ImGui::GetID("PrimitiveEditorDockspace");

        ImGui::DockSpaceOverViewport(dockspaceID, viewport, dockspaceFlags);

        m_hierarchyPanel.OnRender();
        m_inspectorPanel.OnRender();

        if (m_selectedEntity)
        {
            ImGui::Begin("Selection Debug");

            ImGui::Text(
                "Selected Entity ID: %u",
                static_cast<unsigned int>(
                    m_selectedEntity.GetID()));

            ImGui::End();
        }

        m_viewportPanel.OnRender();

        if (m_engine)
        {
            const Window &window = m_engine->GetWindow();

            if (window.GetHeight() > 0)
            {
                const float aspectRatio = static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight());

                m_inspectorPanel.SetAspectRatio(aspectRatio);
            }
        }
    }
}