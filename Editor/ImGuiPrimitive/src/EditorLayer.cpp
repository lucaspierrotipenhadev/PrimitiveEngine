#include "Primitive/Renderer/FrameBuffer.hpp"
#include "Primitive/ImGuiPrimitive/EditorLayer.hpp"

#include "Primitive/Core/Engine.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLFrameBuffer.hpp"

#include "Primitive/Scene/Components/CameraComponent.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"

#include <cstdint>

#include <imgui.h>
#include <ImGuizmo.h>

namespace primitive
{
    void EditorLayer::OnAttach(Engine &engine)
    {
        m_engine = &engine;
        m_engine->SetRenderActiveScene(false);
        m_engine->SetUpdateActiveScene(false);
        m_editorScene = engine.GetActiveScene();
        m_hierarchyPanel.SetScene(m_editorScene);
        m_hierarchyPanel.SetSelectionContext(&m_selectedEntity);
        m_inspectorPanel.SetSelectionContext(&m_selectedEntity);

        m_inspectorPanel.SetReadOnly(false);
        m_hierarchyPanel.SetReadOnly(false);

        FramebufferSpecification specification;

        specification.width = 1280;
        specification.height = 720;

        m_sceneFramebuffer = m_engine->GetRenderer().CreateFramebuffer(specification);
    }

    void EditorLayer::OnDetach()
    {
        if (m_engine)
        {
            m_engine->SetRenderActiveScene(true);
            m_engine->SetUpdateActiveScene(true);
        }

        m_inspectorPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetScene(nullptr);
        m_engine = nullptr;
    }

    void EditorLayer::OnUpdate(float deltaTime)
    {
        (void)deltaTime;

        if (!m_engine || !m_sceneFramebuffer)
        {
            return;
        }

        Scene* scene = GetActiveEditorScene();

        if(!scene)
        {
            return;
        }

        if (m_sceneState == SceneState::Play)
        {
           scene->Update(deltaTime, m_engine->GetEventBus());     
        }

        const glm::vec2 viewportSize = m_viewportPanel.GetSize();

        if (viewportSize.x > 0.0f && viewportSize.y > 0.0f)
        {
            const auto width =
                static_cast<std::uint32_t>(
                    viewportSize.x);

            const auto height =
                static_cast<std::uint32_t>(
                    viewportSize.y);

            const auto &specification =
                m_sceneFramebuffer
                    ->GetSpecification();

            if (specification.width != width ||
                specification.height != height)
            {
                m_sceneFramebuffer->Resize(width, height);

                const float aspectRatio =
                    static_cast<float>(width) /
                    static_cast<float>(height);

                scene->ForEach<
                    CameraComponent>(
                    [aspectRatio](
                        EntityID,
                        CameraComponent &camera)
                    {
                        camera.UppdateProjection(
                            aspectRatio);
                    });

                m_inspectorPanel
                    .SetAspectRatio(
                        aspectRatio);
            }
        }

        m_sceneFramebuffer->Bind();

        auto& renderer = m_engine->GetRenderer();

        renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        scene->Render(renderer);

        m_sceneFramebuffer->Unbind();

        renderer.SetViewport(0, 0, 
            static_cast<std::uint32_t>(m_engine->GetWindow().GetWidth()),
            static_cast<std::uint32_t>(m_engine->GetWindow().GetHeight()));
    }

    void EditorLayer::OnRender()
    {
        constexpr ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        const ImGuiID dockspaceID = ImGui::GetID("PrimitiveEditorDockspace");

        ImGui::DockSpaceOverViewport(dockspaceID, viewport, dockspaceFlags);

        DrawToolBar();

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

        if (m_sceneFramebuffer)
        {
            m_viewportPanel.SetTextureID(m_sceneFramebuffer->GetColorAttachmentID());
        }

        m_viewportPanel.OnRender(
            [this]()
            {
                DrawGuizmo();
            });

        if (m_engine)
        {
            const Window &window = m_engine->GetWindow();

            if (m_engine && m_sceneState ==  SceneState::Edit && m_viewportPanel.IsFocused() && !ImGuizmo::IsUsing())
            {
                auto &input = m_engine->GetInput();

                if (input.IsKeyPressed(Key::W))
                {
                    m_gizmoOperation = GizmoOperation::Translate;
                }

                if (input.IsKeyPressed(Key::E))
                {
                    m_gizmoOperation = GizmoOperation::Rotate;
                }

                if (input.IsKeyPressed(Key::R))
                {
                    m_gizmoOperation = GizmoOperation::Scale;
                }
            }
        }
    }

    void EditorLayer::DrawGuizmo()
    {
        if (!m_engine || !m_selectedEntity || !m_selectedEntity.HasComponent<TransformComponent>())
        {
            return;
        }

        if (m_sceneState != SceneState::Edit)
        {
            return;
        }

        Scene* scene = GetActiveEditorScene();

        if (!scene)
        {
            return;
        }

        CameraComponent *cameraComponent =
            nullptr;

        TransformComponent *cameraTransform =
            nullptr;

        scene->ForEach<
            TransformComponent,
            CameraComponent>(
            [&](EntityID,
                TransformComponent &transform,
                CameraComponent &camera)
            {
                if (!cameraComponent &&
                    camera.primary)
                {
                    cameraComponent =
                        &camera;

                    cameraTransform =
                        &transform;
                }
            });

        if (!cameraComponent ||
            !cameraTransform)
        {
            return;
        }

        auto &selectedTransform =
            m_selectedEntity
                .GetComponent<
                    TransformComponent>()
                .transform;

        glm::mat4 model =
            selectedTransform
                .GetMatrix();

        const glm::mat4 view =
            glm::inverse(
                cameraTransform
                    ->transform
                    .GetMatrix());

        const glm::mat4 projection =
            cameraComponent
                ->camera
                .GetProjection();

        const glm::vec2 viewportPosition =
            m_viewportPanel
                .GetPosition();

        const glm::vec2 viewportSize =
            m_viewportPanel
                .GetSize();

        if (viewportSize.x <= 0.0f ||
            viewportSize.y <= 0.0f)
        {
            return;
        }

        ImGuizmo::SetOrthographic(
            cameraComponent
                ->projectionType ==
            CameraProjectionType::
                Orthographic);

        ImGuizmo::SetDrawlist();

        ImGuizmo::SetRect(
            viewportPosition.x,
            viewportPosition.y,
            viewportSize.x,
            viewportSize.y);

        ImGuizmo::OPERATION operation =
            ImGuizmo::TRANSLATE;

        switch (m_gizmoOperation)
        {
        case GizmoOperation::Translate:
            operation =
                ImGuizmo::TRANSLATE;
            break;

        case GizmoOperation::Rotate:
            operation =
                ImGuizmo::ROTATE;
            break;

        case GizmoOperation::Scale:
            operation =
                ImGuizmo::SCALE;
            break;
        }

        ImGuizmo::Manipulate(
            glm::value_ptr(view),
            glm::value_ptr(projection),
            operation,
            ImGuizmo::LOCAL,
            glm::value_ptr(model));

        if (ImGuizmo::IsUsing())
        {
            // aplicar model de volta ao Transform
            float translation[3];
            float rotation[3];
            float scale[3];

            ImGuizmo::DecomposeMatrixToComponents(
                glm::value_ptr(model),
                translation,
                rotation,
                scale);

            selectedTransform.SetPosition(
                glm::vec3{
                    translation[0],
                    translation[1],
                    translation[2]});

            selectedTransform.SetRotation(
                glm::vec3{
                    rotation[0],
                    rotation[1],
                    rotation[2]});

            selectedTransform.SetScale(
                glm::vec3{
                    scale[0],
                    scale[1],
                    scale[2]});
        }
    }

    void EditorLayer::OnScenePlay()
    {
        if (m_sceneState != SceneState::Edit || !m_editorScene)
        {
            return;
        }

        m_runtimeScene = m_editorScene->Clone();

        if(!m_runtimeScene)
        {
            return;
        }

        m_sceneState = SceneState::Play;
        m_selectedEntity = {};
        m_hierarchyPanel.SetScene(m_runtimeScene.get());
        m_hierarchyPanel.SetReadOnly(true);
        m_inspectorPanel.SetReadOnly(true);
    }

    void EditorLayer::OnSceneStop()
    {
        if (m_sceneState != SceneState::Play)
        {
            return;
        }

        if(!m_editorScene)
        {
            return;
        }

        m_selectedEntity = {};
        m_runtimeScene.reset();
        m_sceneState = SceneState::Edit;
        m_hierarchyPanel.SetScene(m_editorScene);
        m_hierarchyPanel.SetReadOnly(false);
        m_inspectorPanel.SetReadOnly(false);
    }

    void EditorLayer::DrawToolBar()
    {
        ImGui::Begin("ToolBar", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        const float buttonWidth = 70.0f;
        const float availableWidth = ImGui::GetContentRegionAvail().x;

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (availableWidth - buttonWidth) * 0.5f);
        const char *label = m_sceneState == SceneState::Edit ? "Play" : "Stop";

        if (ImGui::Button(label, ImVec2{buttonWidth, 0.0f}))
        {
            if (m_sceneState == SceneState::Edit)
            {
                OnScenePlay();
            }
            else
            {
                OnSceneStop();
            }
        }
        ImGui::End();
    }

    Scene *EditorLayer::GetActiveEditorScene()
    {
        if (m_sceneState == SceneState::Play)
        {
            return m_runtimeScene.get();
        }

        return m_editorScene;
    }

    const Scene* EditorLayer::GetActiveEditorScene() const
    {
        if (m_sceneState == SceneState::Play)
        {
            return m_runtimeScene.get();
        }

        return m_editorScene;
    }
}