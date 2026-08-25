#pragma once

#include "Primitive/Scene/Entity.hpp"

namespace primitive
{
    class Collider;
    class InspectorPanel
    {
    public:
        InspectorPanel() = default;

        explicit InspectorPanel(Entity* selectedEntity);

        void SetSelectionContext(Entity* selectedEntity);
        void OnRender();
        void SetAspectRatio(float aspectRatio);
    
    private:
        Entity* m_selectedEntity{nullptr};
        float m_aspectRatio{16.0f / 9.0f};

        void DrawColliderProperties(Collider& collider);
    };
}