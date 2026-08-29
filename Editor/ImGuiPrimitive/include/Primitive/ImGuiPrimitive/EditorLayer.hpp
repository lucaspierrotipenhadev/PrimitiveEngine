#pragma once

#include <memory>

#include "Primitive/Core/Layer.hpp"

#include "Primitive/ImGuiPrimitive/Panels/HierarchyPanel.hpp"
#include "Primitive/ImGuiPrimitive/Panels/InspectorPanel.hpp"
#include "Primitive/ImGuiPrimitive/Panels/ViewportPanel.hpp"

#include "Primitive/Scene/Entity.hpp"

#include <imgui.h>
#include <ImGuizmo.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace primitive
{
    class Engine;
    class Framebuffer;

    enum class GizmoOperation
    {
        Translate,
        Rotate,
        Scale
    };

    enum class SceneState
    {
        Edit,
        Play
    };

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
        [[nodiscard]]
        Scene* GetActiveEditorScene();

        [[nodiscard]]
        const Scene* GetActiveEditorScene() const;

    private:
        Engine* m_engine{nullptr};
        HierarchyPanel m_hierarchyPanel;
        InspectorPanel m_inspectorPanel;
        ViewportPanel m_viewportPanel;
        Entity m_selectedEntity;
        
        std::unique_ptr<Framebuffer> m_sceneFramebuffer;
        GizmoOperation m_gizmoOperation{GizmoOperation::Translate};

        Scene* m_editorScene{nullptr};
        std::unique_ptr<Scene> m_runtimeScene;
        SceneState m_sceneState={SceneState::Edit};


        void DrawGuizmo();
        void OnScenePlay();
        void OnSceneStop();
        void DrawToolBar();
    };
}