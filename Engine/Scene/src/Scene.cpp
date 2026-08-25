#include "Primitive/Scene/Scene.hpp"

#include <stdexcept>
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Primitive/Core/EventBus.hpp"

#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/ModelRendererComponent.hpp"
#include "Primitive/Scene/Components/CameraComponent.hpp"
#include "Primitive/Scene/Components/TagComponent.hpp"

#include "Primitive/Renderer/Renderer.hpp"
#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/Material.hpp"
#include "Primitive/Renderer/Model.hpp"

namespace primitive
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        const EntityID id =
            m_entityManager.Create();

        m_componentManager
        .Add<TagComponent>(
            id,
            name
        );

        return Entity{
            id,
            this};
    }

    void Scene::DestroyEntity(
        Entity entity)
    {
        const EntityID id =
            entity.GetID();

        ValidateEntity(id);

        m_componentManager.RemoveAll(id);

        m_entityManager.Destroy(id);
    }

    bool Scene::IsEntityAlive(
        EntityID entity) const
    {
        return m_entityManager.IsAlive(
            entity);
    }

    std::size_t
    Scene::GetEntityCount() const
    {
        return m_entityManager
            .GetAliveCount();
    }

    void Scene::Clear()
    {
        m_physicsWorld.Clear();
        m_physicsTimeStep.Reset();
        m_componentManager.Clear();
        m_entityManager.Clear();
    }

    void Scene::ValidateEntity(
        EntityID entity) const
    {
        if (entity == NullEntity)
        {
            throw std::runtime_error(
                "Invalid entity.");
        }

        if (!m_entityManager.IsAlive(entity))
        {
            throw std::runtime_error(
                "Entity is not alive.");
        }
    }

    void Scene::Update(float deltaTime, EventBus& eventBus)
    {
        AdvancePhysics(deltaTime, eventBus);
    }

    void Scene::Render(Renderer &renderer)
    {
        glm::mat4 view{1.0f};
        glm::mat4 projection{1.0f};

        bool hasPrimaryCamera = false;

        ForEach<TransformComponent, CameraComponent>(
            [&](
                EntityID,
                TransformComponent &transform,
                CameraComponent &camera)
            {
                if (hasPrimaryCamera || !camera.primary)
                {
                    return;
                }

                view = glm::inverse(transform.transform.GetMatrix());

                projection = camera.camera.GetProjection();

                hasPrimaryCamera = true;
            });

        if (!hasPrimaryCamera)
        {
            return;
        }

        ForEach<TransformComponent, ModelRendererComponent>(
            [&](
                EntityID,
                TransformComponent &transform,
                ModelRendererComponent &modelRenderer)
            {
                if (!modelRenderer.model || !modelRenderer.material)
                {
                    return;
                }

                const glm::mat4 model = transform.transform.GetMatrix();
                const auto &shader = modelRenderer.material->GetShader();

                if (!shader)
                {
                    return;
                }

                shader->Bind();

                shader->SetMat4("u_Model", glm::value_ptr(model));
                shader->SetMat4("u_View", glm::value_ptr(view));
                shader->SetMat4("u_Projection", glm::value_ptr(projection));
                shader->SetFloat3("u_LightDirection", -1.0f, -1.0f, -1.0f);
                shader->SetFloat3("u_LightColor", 1.0f, 1.0f, 1.0f);

                renderer.DrawModel(*modelRenderer.model, *modelRenderer.material);
            });
    }

    PhysicsWorld &Scene::GetPhysicsWorld()
    {
        return m_physicsWorld;
    }

    const PhysicsWorld &Scene::GetPhysicsWorld() const
    {
        return m_physicsWorld;
    }

    void Scene::SetFixedTimeStep(float fixedTimeStep)
    {
        m_physicsTimeStep.SetStep(fixedTimeStep);
    }

    void Scene::AdvancePhysics(float deltaTime, EventBus& eventBus)
    {
        if(deltaTime <= 0) {return;}

        m_physicsTimeStep.AddTime(deltaTime);

        std::uint32_t stepCount = 0;

        while(m_physicsTimeStep.CanStep() && stepCount < m_maxPhysicsStepsPerFrame)
        {
            const float fixedDeltaTime = m_physicsTimeStep.GetStep();
            m_physicsWorld.Step(*this, fixedDeltaTime);
            m_physicsWorld.PublishCollisionEvents(eventBus);
            m_physicsTimeStep.ConsumeStep();
            ++stepCount;
        }

        if(stepCount == m_maxPhysicsStepsPerFrame && m_physicsTimeStep.CanStep())
        {
            m_physicsTimeStep.Reset();
        }

    }

    float Scene::GetFixedTimeStep() const
    {
        return m_physicsTimeStep.GetStep();
    }
}