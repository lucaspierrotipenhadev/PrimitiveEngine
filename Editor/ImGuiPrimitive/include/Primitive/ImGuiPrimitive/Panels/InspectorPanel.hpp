#pragma once

#include "Primitive/Scene/Entity.hpp"

namespace primitive
{
    class Collider;
    class TransformComponent;
    class CameraComponent;
    class ModelRendererComponent;
    class RigidBodyComponent;
    class InspectorPanel
    {
    public:
        InspectorPanel() = default;

        explicit InspectorPanel(Entity *selectedEntity);

        void SetSelectionContext(Entity *selectedEntity);
        void OnRender();
        void SetAspectRatio(float aspectRatio);
        void SetReadOnly(bool readOnly);

        template <typename Component, typename DrawFunction>
        bool DrawComponent(const char *name, Entity entity, DrawFunction &&drawFunction, bool removable = true);

    private:
        Entity *m_selectionContext{nullptr};
        float m_aspectRatio{16.0f / 9.0f};

        bool m_readOnly{false};

        void DrawAddComponentMenu();
        void DrawColliderProperties(Collider &collider);
        void DrawTransformProperties(TransformComponent &transformComponent);
        void DrawCameraProperties(CameraComponent &cameraComponent);
        void DrawModelProperties(ModelRendererComponent &modelRendererComponent);
        void DrawRigidBodyProperties(RigidBodyComponent &rigidBodyComponent);
    };
}