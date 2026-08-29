#include "Primitive/ImGuiPrimitive/Panels/InspectorPanel.hpp"

#include "Primitive/Scene/Components/TagComponent.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/CameraComponent.hpp"
#include "Primitive/Scene/Components/ModelRendererComponent.hpp"
#include "Primitive/Scene/Components/RigidbodyComponent.hpp"
#include "Primitive/Scene/Components/BoxColliderComponent.hpp"
#include "Primitive/Scene/Components/SphereColliderComponent.hpp"

#include "Primitive/Scene/Scene.hpp"

#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Renderer/Material.hpp"
#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/Mesh.hpp"
#include "Primitive/Renderer/Texture.hpp"

#include "Primitive/Physics/Collider.hpp"

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>

namespace primitive
{
    InspectorPanel::InspectorPanel(Entity *selectedEntity) : m_selectionContext(selectedEntity)
    {
    }

    void InspectorPanel::SetSelectionContext(Entity *selectedEntity)
    {
        m_selectionContext = selectedEntity;
    }

    void InspectorPanel::OnRender()
    {
        ImGui::Begin("Inspector");
        ImGui::BeginDisabled(m_readOnly);

        if (!m_selectionContext || !m_selectionContext->IsValid())
        {
            ImGui::TextDisabled("No entity selected.");
            ImGui::EndDisabled();
            ImGui::End();
            return;
        }

        Entity &entity =
            *m_selectionContext;

        if (entity.HasComponent<TagComponent>())
        {
            const auto &tag =
                entity.GetComponent<TagComponent>();

            ImGui::Text(
                "%s",
                tag.tag.c_str());
        }
        else
        {
            ImGui::Text(
                "Entity %u",
                static_cast<unsigned int>(
                    entity.GetID()));
        }

        ImGui::TextDisabled(
            "Entity ID: %u",
            static_cast<unsigned int>(
                entity.GetID()));

        ImGui::Separator();

        // transform
        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                DrawTransformProperties(entity.GetComponent<TransformComponent>());
            }
        }

        // camera
        if (entity.HasComponent<CameraComponent>())
        {
            if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
            {
                DrawCameraProperties(entity.GetComponent<CameraComponent>());
            }
        }

        // model
        if (entity.HasComponent<ModelRendererComponent>())
        {
            if (ImGui::CollapsingHeader("Model Renderer"))
            {
                DrawModelProperties(entity.GetComponent<ModelRendererComponent>());
            }
        }

        // Rigid Body
        if (entity.HasComponent<RigidBodyComponent>())
        {
            if (ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_DefaultOpen))
            {
                DrawRigidBodyProperties(entity.GetComponent<RigidBodyComponent>());
            }
        }

        // Collider
        if (entity.HasComponent<BoxColliderComponent>())
        {
            if (ImGui::CollapsingHeader("Box Collider"))
            {
                auto &component = entity.GetComponent<BoxColliderComponent>();

                DrawColliderProperties(component.collider);

                glm::vec3 halfExtents = component.halfExtends;

                if (ImGui::DragFloat3("Half Extents", &halfExtents.x, 0.05f, 0.001f, 10000.0f))
                {
                    halfExtents = glm::max(halfExtents, glm::vec3{0.001f});
                    component.halfExtends = halfExtents;
                }
            }
        }

        if (entity.HasComponent<SphereColliderComponent>())
        {
            if (ImGui::CollapsingHeader("Sphere Collider"))
            {
                ImGui::TextDisabled("SphereColliderComponent");
            }
        }

        // Add components
        if (!entity.HasComponent<ModelRendererComponent>())
        {
            if (ImGui::MenuItem("Model Renderer"))
            {
                entity.AddComponent<ModelRendererComponent>();
                ImGui::CloseCurrentPopup();
            }
        }

        ImGui::Separator();

        //transform
        if (DrawComponent<TransformComponent>("Transform", entity, [this](TransformComponent &component)
            {
                DrawTransformProperties(component);
            }, false))
        {
            removeTransform = false;
        }
        //camera
        if (DrawComponent<CameraComponent>("Camera", entity, [this](CameraComponent &component)
            {
                DrawCameraProperties(component);
            }))
        {
            removeCamera = true;
        }
        //model
        if (DrawComponent<ModelRendererComponent>("Model", entity, [this](ModelRendererComponent &component)
            {
                DrawModelProperties(component);
            }))
        {
            removeModelRenderer = true;
        }
        //rigid body
        if (DrawComponent<RigidBodyComponent>("RigidBody", entity, [this](RigidBodyComponent &component)
            {
                DrawRigidBodyProperties(component);
            }))
        {
            removeRigidBody = true;
        }
        //collider
        if (DrawComponent<BoxColliderComponent>("Collider", entity, [this](BoxColliderComponent &component)
            {
                DrawColliderProperties(component.collider);
            }))
        {
            removeBoxCollider = true;
        }

        //remoções - transform
        if(removeTransform)
        {
            entity.RemoveComponent<TransformComponent>();
        }

        //remoções - camera
        if(removeCamera)
        {
            entity.RemoveComponent<CameraComponent>();
        }

        //remoções - model
        if(removeModelRenderer)
        {
            entity.RemoveComponent<ModelRendererComponent>();
        }

        //remoções - rigid body
        if(removeRigidBody)
        {
            entity.RemoveComponent<RigidBodyComponent>();
        }

        //remoções - box collider
        if(removeBoxCollider)
        {
            entity.RemoveComponent<BoxColliderComponent>();
        }

        ImGui::Separator();

        if (ImGui::Button("Add Component", ImVec2{-1.0f, 0.0f}))
        {
            ImGui::OpenPopup("AddComponentPopup");
        }

        if (ImGui::BeginPopup("AddComponentPopup"))
        {
            DrawAddComponentMenu();
            ImGui::EndPopup();
        }

        ImGui::EndDisabled();
        ImGui::End();
    }

    void InspectorPanel::SetAspectRatio(float aspectRatio)
    {
        if (aspectRatio > 0.0f)
        {
            m_aspectRatio = aspectRatio;
        }
    }

    void InspectorPanel::DrawAddComponentMenu()
    {
        if (!m_selectionContext || !*m_selectionContext)
        {
            return;
        }

        Entity &entity = *m_selectionContext;

        if (!entity.HasComponent<TransformComponent>())
        {
            if (ImGui::MenuItem("Transform"))
            {
                entity.AddComponent<TransformComponent>();
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<CameraComponent>())
        {
            if (ImGui::MenuItem("Camera"))
            {
                entity.AddComponent<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<ModelRendererComponent>())
        {
            if (ImGui::MenuItem("Model"))
            {
                entity.AddComponent<ModelRendererComponent>();
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<RigidBodyComponent>())
        {
            if (ImGui::MenuItem("Rigid Body"))
            {
                entity.AddComponent<RigidBodyComponent>();
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<BoxColliderComponent>())
        {
            if (ImGui::MenuItem("Box Collider"))
            {
                entity.AddComponent<BoxColliderComponent>();
                ImGui::CloseCurrentPopup();
            }
        }

        if (!entity.HasComponent<SphereColliderComponent>())
        {
            if (ImGui::MenuItem("Sphere Collider"))
            {
                entity.AddComponent<SphereColliderComponent>();
                ImGui::CloseCurrentPopup();
            }
        }
    }

    template <typename Component, typename DrawFunction>
    bool InspectorPanel::DrawComponent(const char *name, Entity entity, DrawFunction &&drawFunction, bool removable)
    {
        if (!entity.HasComponent<Component>())
        {
            return false;
        }

        auto &component = entity.GetComponent<Component>();

        ImGui::PushID(name);

        const bool open = ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_DefaultOpen);
        bool removeRequested = false;

        if (removable)
        {
            if (ImGui::BeginPopupContextItem("ComponentContext"))
            {
                if (ImGui::MenuItem("Remove Component"))
                {
                    removeRequested = true;
                }

                ImGui::EndPopup();
            }
        }

        if (open)
        {
            drawFunction(component);
        }

        ImGui::PopID();

        return removeRequested;
    }

    void InspectorPanel::DrawColliderProperties(Collider &collider)
    {
        ImGui::Checkbox("Enabled", &collider.enabled);
        ImGui::Checkbox("Is Trigger", &collider.isTrigger);
        ImGui::DragFloat3("Offset", &collider.offset.x, 0.5f);

        if (ImGui::DragFloat3("Friction", &collider.friction, 0.01f, 0.0f, 1.0f))
        {
            collider.friction = glm::clamp(collider.friction, 0.0f, 1.0f);
        }

        if (ImGui::DragFloat("Restitution", &collider.restitution, 0.0f, 1.0f))
        {
            collider.restitution = glm::clamp(collider.restitution, 0.0f, 1.0f);
        }
    }

    void InspectorPanel::DrawTransformProperties(TransformComponent &transformComponent)
    {
        auto &transform = transformComponent.transform;

        glm::vec3 position = transform.GetPosition();
        glm::vec3 rotation = transform.GetRotation();
        glm::vec3 scale = transform.GetScale();

        if (ImGui::DragFloat3("Position", &position.x, 0.05f))
        {
            transform.SetPosition(position);
        }

        if (ImGui::DragFloat3("Rotation", &rotation.x, 0.5f))
        {
            transform.SetRotation(rotation);
        }

        if (ImGui::DragFloat3("Scale", &scale.x, 0.05f))
        {
            transform.SetScale(scale);
        }
    }

    void InspectorPanel::DrawCameraProperties(CameraComponent &cameraComponent)
    {
        auto &component = cameraComponent;
        bool projectionChange = false;
        const char *projectionTypes[] = {"Perspective", "Orthographic"};
        int currentProjection = component.projectionType == CameraProjectionType::Perspective ? 0 : 1;

        if (ImGui::Combo("Projection", &currentProjection, projectionTypes, 2))
        {
            component.projectionType = currentProjection == 0 ? CameraProjectionType::Perspective : CameraProjectionType::Orthographic;
            projectionChange = true;
        }

        if (component.projectionType == CameraProjectionType::Perspective)
        {
            projectionChange |= ImGui::DragFloat("FOV", &component.perspectiveFov, 0.1f, 1.0f, 179.0f);
            projectionChange |= ImGui::DragFloat("Near", &component.perspectiveNear, 0.1f, 1.0f, component.perspectiveFar);
            projectionChange |= ImGui::DragFloat("Far", &component.perspectiveFar, 0.1f, component.perspectiveNear, 10000.0f);
        }
        else
        {
            projectionChange |= ImGui::DragFloat("Size", &component.orthographicSize, 0.1f, 1.0f, 1000.0f);
            projectionChange |= ImGui::DragFloat("Near", &component.orthographicNear, 0.1f);
            projectionChange |= ImGui::DragFloat("Far", &component.orthographicFar, 0.1f);
        }

        ImGui::Checkbox("Primary", &component.primary);

        if (projectionChange)
        {
            component.UppdateProjection(m_aspectRatio);
        }
    }

    void InspectorPanel::DrawModelProperties(ModelRendererComponent &modelRendererComponent)
    {
        auto &component = modelRendererComponent;
        ImGui::Text("Model %s", component.model ? "Loaded" : "None");
        if (component.model)
        {
            ImGui::Text("Path: %s", component.model->GetFilepath().c_str());
            // ImGui::Text("Meshes: %s", component.model->GetMeshes().size());
        }

        ImGui::Text("Material %s", component.material ? "Loaded" : "None");
        if (component.material)
        {
            glm::vec4 color = component.material->GetBaseColor();
            if (ImGui::ColorEdit4("Base Color", &color.x))
            {
                component.material->SetBaseColor(color);
            }

            const auto &texture = component.material->GetAlbedoTexture();

            if (texture)
            {
                ImGui::Text("Texture: %s", texture->GetFilepath().c_str());
            }
        }
    }

    void InspectorPanel::DrawRigidBodyProperties(RigidBodyComponent &rigidBodyComponent)
    {
        auto &rigidBody = rigidBodyComponent;
        const char *bodyTypes[] = {"Static", "Dynamic", "Kinematic"};

        int currentType = 0;

        switch (rigidBody.type)
        {
        case RigidBodyType::Dynamic:
            currentType = 0;
            break;
        case RigidBodyType::Static:
            currentType = 1;
            break;
        case RigidBodyType::Kinematic:
            currentType = 2;
            break;
        }

        if (ImGui::Combo("Body Type", &currentType, bodyTypes, 3))
        {
            switch (currentType)
            {
            case 0:
                rigidBody.type = RigidBodyType::Static;
                break;

            case 1:
                rigidBody.type = RigidBodyType::Dynamic;
                break;

            case 2:
                rigidBody.type = RigidBodyType::Kinematic;
                break;

            default:
                break;
            }
        }

        if (rigidBody.type == RigidBodyType::Dynamic)
        {
            ImGui::DragFloat("Mass", &rigidBody.mass, 0.1f, 0.0001f, 10000.0f);
        }

        if (rigidBody.type != RigidBodyType::Static)
        {
            ImGui::DragFloat3("Velocity", &rigidBody.velocity.x, 0.05f);

            ImGui::TextDisabled("Force: %.2f %.2f %.2f", rigidBody.force.x, rigidBody.force.y, rigidBody.force.z);

            ImGui::Checkbox("Use Gravity", &rigidBody.useGravity);
        }
    }

    void InspectorPanel::SetReadOnly(bool readOnly)
    {
        m_readOnly = readOnly;
    }
}