#include "Primitive/Renderer/FrameBuffer.hpp"
#include "Primitive/ImGuiPrimitive/EditorLayer.hpp"

#include "Primitive/ImGuiPrimitive/FileDialogs.hpp"

#include "Primitive/Core/Engine.hpp"

#include "Primitive/Renderer/OpenGL/OpenGLFrameBuffer.hpp"

#include "Primitive/Scene/Components/CameraComponent.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/SceneSerializer.hpp"

#include "Primitive/Assets/AssetManager.hpp"

#include "Primitive/Project/Project.hpp"

#include <cstdint>

#include <imgui.h>
#include <imgui_internal.h>
#include <ImGuizmo.h>

namespace primitive
{
    EditorLayer::EditorLayer(Project& project, AssetManager& assetManager) : m_project(project), m_assetManager(assetManager)
    {
    }

    void EditorLayer::OnAttach(Engine &engine)
    {
        m_engine = &engine;
        m_engine->SetRenderActiveScene(false);
        m_engine->SetUpdateActiveScene(false);

        m_editorScene = engine.GetActiveScene();

        m_contentBrowserPanel.SetProject(&m_project);
        m_contentBrowserPanel.SetAssetManager(&m_assetManager);

        m_hierarchyPanel.SetSelectionContext(&m_selectedEntity);
        m_inspectorPanel.SetAssetManager(&m_assetManager);
        m_inspectorPanel.SetSelectionContext(&m_selectedEntity);

        NewScene();

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
        m_inspectorPanel.SetAssetManager(nullptr);
        m_hierarchyPanel.SetSelectionContext(nullptr);
        m_hierarchyPanel.SetScene(nullptr);
        m_contentBrowserPanel.SetProject(nullptr);
        m_contentBrowserPanel.SetAssetManager(nullptr);
        m_engine = nullptr;
    }

    void EditorLayer::OnUpdate(float deltaTime)
    {
        (void)deltaTime;

        if (!m_engine || !m_sceneFramebuffer)
        {
            return;
        }

        Scene *scene = GetActiveEditorScene();

        if (!scene)
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

            if (specification.width != width || specification.height != height)
            {
                m_sceneFramebuffer->Resize(width, height);
            }
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

            m_inspectorPanel.SetAspectRatio(aspectRatio);
        }

        m_sceneFramebuffer->Bind();

        auto &renderer = m_engine->GetRenderer();

        renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        scene->Render(renderer);

        m_sceneFramebuffer->Unbind();

        renderer.SetViewport(0, 0,
                             static_cast<std::uint32_t>(m_engine->GetWindow().GetWidth()),
                             static_cast<std::uint32_t>(m_engine->GetWindow().GetHeight()));
    }

    void EditorLayer::OnRender()
    {
        DrawDockspace();
        DrawToolBar();

        m_hierarchyPanel.OnRender();
        m_inspectorPanel.OnRender();
        m_contentBrowserPanel.OnRender();

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

            if (m_engine && m_sceneState == SceneState::Edit && m_viewportPanel.IsFocused() && !ImGuizmo::IsUsing())
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

        Scene *scene = GetActiveEditorScene();

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

            MarkSceneDirty();
        }
    }

    void EditorLayer::OnScenePlay()
    {
        if (m_sceneState != SceneState::Edit || !m_editorScene)
        {
            return;
        }

        m_runtimeScene = m_editorScene->Clone();

        if (!m_runtimeScene)
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

        if (!m_editorScene)
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

    void EditorLayer::DrawMenuBar()
    {
        if (!ImGui::BeginMenuBar())
        {
            return;
        }

        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N", false, m_sceneState == SceneState::Edit))
            {
                NewScene();
            }

            if (ImGui::MenuItem("Open...", "Ctrl+O", false, m_sceneState == SceneState::Edit))
            {
                OpenScene();
            }

            if (ImGui::MenuItem("Save", "Ctrl+S", false, m_sceneState == SceneState::Edit))
            {
                SaveScene();
            }

            if (ImGui::MenuItem("Save As", "Ctrl+Shift+S", false, m_sceneState == SceneState::Edit))
            {
                SaveSceneAs();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
            {
                m_engine->Stop();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scene"))
        {
            if (m_sceneState == SceneState::Edit)
            {
                if (ImGui::MenuItem("Play"))
                {
                    OnScenePlay();
                }
            }
            else
            {
                if (ImGui::MenuItem("Stop"))
                {
                    OnSceneStop();
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window"))
        {
            if (ImGui::MenuItem("Reset Layout"))
            {
                m_resetDockLayout = true;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    void EditorLayer::DrawToolBar()
    {
        ImGui::Begin("ToolBar", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        ImGui::Text("Scene: %s%s", m_currentSceneName.c_str(), m_sceneDirty ? " *" : "");

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

    const Scene *EditorLayer::GetActiveEditorScene() const
    {
        if (m_sceneState == SceneState::Play)
        {
            return m_runtimeScene.get();
        }

        return m_editorScene;
    }

    void EditorLayer::UpdateSceneCameraProjections()
    {
        if (!m_editorScene)
        {
            return;
        }

        const glm::vec2 viewportSize = m_viewportPanel.GetSize();

        if (viewportSize.x <= 0.0f || viewportSize.y <= 0.0f)
        {
            return;
        }

        const float aspectRatio = viewportSize.x / viewportSize.y;

        m_editorScene->ForEach<CameraComponent>(
            [aspectRatio](
                EntityID,
                CameraComponent &camera)
            {
                camera.UppdateProjection(
                    aspectRatio);
            });

        m_inspectorPanel.SetAspectRatio(aspectRatio);
    }

    void EditorLayer::SetCurrentScenePath(const std::filesystem::path &path)
    {
        m_currentScenePath = path;

        if (!path.empty())
        {
            m_currentSceneName = path.stem().string();
        }
        else
        {
            m_currentSceneName = "Untitled";
        }
    }

    void EditorLayer::ClearCurrentScenePath()
    {
        m_currentScenePath.clear();
        m_currentSceneName = "Untitled";
    }

    bool EditorLayer::HasCurrentScenePath()
    {
        return !m_currentScenePath.empty();
    }

    const std::filesystem::path &EditorLayer::GetCurrentScenePath() const
    {
        return m_currentScenePath;
    }

    const std::string &EditorLayer::GetCurrentSceneName() const
    {
        return m_currentSceneName;
    }

    void EditorLayer::NewScene()
    {
        if (!m_engine)
        {
            return;
        }

        if (m_sceneState == SceneState::Play)
        {
            OnSceneStop();
        }

        m_selectedEntity = {};

        SceneSerializer serialize(*m_editorScene, m_engine->GetResourceManager());

        if (!serialize.Deserialize("Assets/Scenes/Templates/DefaultScene.pscene"))
        {
            m_editorScene->Clear();
        }

        ClearCurrentScenePath();
        ClearSceneDirty();
        UpdateSceneCameraProjections();

        m_hierarchyPanel.SetScene(m_editorScene);
        m_hierarchyPanel.SetReadOnly(false);
        m_inspectorPanel.SetReadOnly(false);
    }

    bool EditorLayer::SaveScene()
    {
        if (!m_editorScene || m_sceneState != SceneState::Edit)
        {
            return false;
        }

        if (!HasCurrentScenePath())
        {
            return SaveSceneAs();
        }

        return SaveSceneToPath(GetCurrentScenePath());
    }

    bool EditorLayer::SaveSceneAs()
    {
        if (!m_editorScene || m_sceneState != SceneState::Edit)
        {
            return false;
        }

        const auto selectedPath = FileDialogs::SaveScene();

        if (!selectedPath)
        {
            return false;
        }
        std::filesystem::path path = *selectedPath;

        if (path.extension() != ".pscene")
        {
            path.replace_extension(".pscene");
        }

        return SaveSceneToPath(path);
    }

    bool EditorLayer::SaveSceneToPath(const std::filesystem::path &path)
    {
        if (!m_editorScene || m_sceneState != SceneState::Edit || path.empty())
        {
            return false;
        }

        SceneSerializer serializer(*m_editorScene, m_engine->GetResourceManager());

        if (!serializer.Serialize(path))
        {
            return false;
        }

        SetCurrentScenePath(path);
        ClearSceneDirty();

        return true;
    }

    bool EditorLayer::OpenScene()
    {
        if (!m_editorScene || m_sceneState != SceneState::Edit)
        {
            return false;
        }

        const auto selectedPath = FileDialogs::OpenScene();

        if (!selectedPath)
        {
            return false;
        }

        ClearSceneDirty();

        return OpenScene(*selectedPath);
    }

    bool EditorLayer::OpenScene(const std::filesystem::path &path)
    {
        if (!m_editorScene || m_sceneState != SceneState::Edit)
        {
            return false;
        }

        if (path.extension() != ".pscene")
        {
            return false;
        }

        m_selectedEntity = {};

        SceneSerializer serializer(*m_editorScene, m_engine->GetResourceManager());

        if (!serializer.Deserialize(path))
        {
            return false;
        }

        SetCurrentScenePath(path);

        m_hierarchyPanel.SetScene(m_editorScene);
        m_hierarchyPanel.SetReadOnly(false);
        m_inspectorPanel.SetReadOnly(false);

        UpdateSceneCameraProjections();
        ClearSceneDirty();

        return true;
    }

    void EditorLayer::MarkSceneDirty()
    {
        if (m_sceneState == SceneState::Edit)
        {
            m_sceneDirty = true;
        }
    }

    void EditorLayer::ClearSceneDirty()
    {
        m_sceneDirty = false;
    }

    bool EditorLayer::IsSceneDirty() const
    {
        return m_sceneDirty;
    }

    void EditorLayer::SetupDefaultDockLayout(ImGuiID dockspaceID, const ImVec2 &dockspaceSize)
    {
        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceID, dockspaceSize);

        ImGuiID dockMain = dockspaceID;

        ImGuiID dockLeft = 0;
        ImGuiID dockRight = 0;
        ImGuiID dockBottom = 0;

        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.20f, &dockLeft, &dockMain);
        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Right, 0.25f, &dockRight, &dockMain);
        ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.30f, &dockBottom, &dockMain);

        ImGui::DockBuilderDockWindow("Hierarchy", dockLeft);
        ImGui::DockBuilderDockWindow("Inspector", dockRight);
        ImGui::DockBuilderDockWindow("Viewport", dockMain);
        ImGui::DockBuilderDockWindow("Content Browser", dockBottom);

        ImGui::DockBuilderFinish(dockspaceID);
    }

    void EditorLayer::DrawDockspace()
    {
        static bool dockspaceOpen = true;

        ImGuiWindowFlags windowFlags =
            ImGuiWindowFlags_MenuBar |
            ImGuiWindowFlags_NoDocking;

        const ImGuiViewport *viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        windowFlags |=
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0.0f, 0.0f});

        ImGui::Begin("PrimitiveDockspace", &dockspaceOpen, windowFlags);
        ImGui::PopStyleVar(3);

        DrawMenuBar();

        const ImGuiID dockspaceID = ImGui::GetID("PrimitiveEditorDockspace");

        if (m_resetDockLayout || ImGui::DockBuilderGetNode(dockspaceID) == nullptr)
        {
            SetupDefaultDockLayout(dockspaceID, viewport->WorkSize);
            m_resetDockLayout = false;
        }

        ImGui::DockSpace(dockspaceID, ImVec2{0.0f, 0.0f}, ImGuiDockNodeFlags_None);

        ImGui::End();
    }

    void EditorLayer::HandleEditorShortcuts()
    {
        if (!m_engine || m_sceneState != SceneState::Edit)
        {
            return;
        }

        auto &input = m_engine->GetInput();

        const bool control =
            input.IsKeyDown(Key::LeftCtrl) ||
            input.IsKeyDown(Key::RightCtrl);

        const bool shift =
            input.IsKeyDown(Key::LeftShift) ||
            input.IsKeyDown(Key::RightShift);

        if (!control)
        {
            return;
        }

        if (input.IsKeyPressed(Key::N))
        {
            NewScene();
        }

        if (input.IsKeyPressed(Key::O))
        {
            OpenScene();
        }

        if (input.IsKeyPressed(Key::S))
        {
            if (shift)
            {
                SaveSceneAs();
            }
            else
            {
                SaveScene();
            }
        }
    }
}