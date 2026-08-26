#pragma once

#include <memory>

#include "Primitive/Core/Layer.hpp"

#include "Primitive/ImGuiPrimitive/Panels/HierarchyPanel.hpp"
#include "Primitive/ImGuiPrimitive/Panels/InspectorPanel.hpp"
#include "Primitive/ImGuiPrimitive/Panels/ViewportPanel.hpp"

#include "Primitive/Scene/Entity.hpp"

namespace primitive
{
    class Engine;
    class Framebuffer;

    class EditorLayer final : public Layer
    {
    public:
        EditorLayer() = default;
        ~EditorLayer() override = default;

        EditorLayer(
            const EditorLayer&) = delete;

        EditorLayer& operator=(
            const EditorLayer&) = delete;

        void OnAttach(
            Engine& engine
        ) override;

        void OnDetach() override;

        void OnUpdate(
            float deltaTime
        ) override;

        void OnRender() override;

    private:
        Engine* m_engine{nullptr};
        HierarchyPanel m_hierarchyPanel;
        InspectorPanel m_inspectorPanel;
        ViewportPanel m_viewportPanel;
        Entity m_selectedEntity;
        std::unique_ptr<Framebuffer> m_sceneFramebuffer;
    };
}