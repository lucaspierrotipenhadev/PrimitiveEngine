#include "Primitive/Scene/SceneSerializer.hpp"

#include "Primitive/Scene/Scene.hpp"

#include "Primitive/Resources/Resource.hpp"
#include "Primitive/Resources/ResourceManager.hpp"

#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Renderer/Material.hpp"
#include "Primitive/Renderer/Texture.hpp"
#include "Primitive/Renderer/Shader.hpp"

#include "Primitive/Scene/Components/TagComponent.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/CameraComponent.hpp"
#include "Primitive/Scene/Components/RigidBodyComponent.hpp"
#include "Primitive/Scene/Components/ModelRendererComponent.hpp"
#include "Primitive/Scene/Components/BoxColliderComponent.hpp"

#include <nlohmann/json.hpp>

#include <fstream>

namespace primitive
{
    using json = nlohmann::json;

    SceneSerializer::SceneSerializer(Scene &scene, ResourceManager &resourceManager) : m_scene(scene), m_resourceManager(resourceManager)
    {
    }

    bool SceneSerializer::Serialize(const std::filesystem::path &filepath)
    {
        json sceneJson;

        sceneJson["scene"] = "Scene";
        sceneJson["entities"] = json::array();

        m_scene.ForEachEntity(
            [&](EntityID entityID)
            {
                json entityJson;

                entityJson["id"] = static_cast<std::uint32_t>(entityID);

                if (m_scene.HasComponent<TagComponent>(entityID))
                {
                    const auto &tag = m_scene.GetComponent<TagComponent>(entityID);
                    entityJson["tag"] = tag.tag;
                }
                if (m_scene.HasComponent<TransformComponent>(entityID))
                {
                    const auto &transform = m_scene.GetComponent<TransformComponent>(entityID);

                    const glm::vec3 position = transform.transform.GetPosition();
                    const glm::vec3 scale = transform.transform.GetScale();
                    const glm::vec3 rotation = transform.transform.GetRotation();

                    entityJson["transform"] = {
                        {"position",
                         {position.x,
                          position.y,
                          position.z}},
                        {"rotation",
                         {rotation.x,
                          rotation.y,
                          rotation.z}},
                        {"scale",
                         {scale.x,
                          scale.y,
                          scale.z}}};
                }
                if (m_scene.HasComponent<CameraComponent>(entityID))
                {
                    const auto &camera = m_scene.GetComponent<CameraComponent>(entityID);
                    if (camera.projectionType == CameraProjectionType::Perspective)
                    {
                        entityJson["camera"] = {
                            {"primary", camera.primary},
                            {"type", camera.projectionType},
                            {"near", camera.perspectiveNear},
                            {"far", camera.perspectiveFar},
                            {"fov", camera.perspectiveFov}};
                    }
                    if (camera.projectionType == CameraProjectionType::Orthographic)
                    {
                        entityJson["camera"] = {
                            {"primary", camera.primary},
                            {"type", camera.projectionType},
                            {"near", camera.orthographicNear},
                            {"far", camera.orthographicFar},
                            {"size", camera.orthographicSize}};
                    }
                }
                if (m_scene.HasComponent<RigidBodyComponent>(entityID))
                {
                    const auto &rigidBody = m_scene.GetComponent<RigidBodyComponent>(entityID);
                    entityJson["rigidBody"] = {
                        {"mass", rigidBody.mass},
                        {"useGravity", rigidBody.useGravity}};
                }
                if (m_scene.HasComponent<BoxColliderComponent>(entityID))
                {
                    const auto &boxColl = m_scene.GetComponent<BoxColliderComponent>(entityID);
                    entityJson["boxCollider"] = {
                        {"halfExtents",
                         {boxColl.halfExtends.x,
                          boxColl.halfExtends.y,
                          boxColl.halfExtends.z}},
                        {"offset",
                         {boxColl.collider.offset.x,
                          boxColl.collider.offset.y,
                          boxColl.collider.offset.z}},
                        {"friction", boxColl.collider.friction},
                        {"restitution", boxColl.collider.restitution},
                        {"isTrigger", boxColl.collider.isTrigger},
                        {"enabled", boxColl.collider.enabled}};
                }
                if (m_scene.HasComponent<ModelRendererComponent>(entityID))
                {
                    const auto &modelRenderer = m_scene.GetComponent<ModelRendererComponent>(entityID);

                    json modelRendererJson;

                    if (modelRenderer.model)
                    {
                        modelRendererJson["model"] = modelRenderer.model->GetFilepath();
                    }
                    else
                    {
                        modelRendererJson["model"] = nullptr;
                    }
                    entityJson["modelRenderer"] = modelRendererJson;

                    if (modelRenderer.material)
                    {
                        json materialJson;

                        const glm::vec4 &baseColor = modelRenderer.material->GetBaseColor();
                        materialJson["baseColor"] = {
                            baseColor.r,
                            baseColor.g,
                            baseColor.b,
                            baseColor.a};

                        if (modelRenderer.material->GetShader())
                        {
                            materialJson["shader"] = modelRenderer.material->GetShader()->GetFilepath();
                        }
                        else
                        {
                            materialJson["shader"] = nullptr;
                        }

                        if (modelRenderer.material->GetAlbedoTexture())
                        {
                            materialJson["albedoTexture"] = modelRenderer.material->GetAlbedoTexture()->GetFilepath();
                        }
                        else
                        {
                            materialJson["albedoTexture"] = nullptr;
                        }
                        modelRendererJson["material"] = materialJson;
                    }
                    else
                    {
                        modelRendererJson["material"] = nullptr;
                    }
                    entityJson["modelRenderer"] = modelRendererJson;
                }
                sceneJson["entities"].push_back(entityJson);
            });

        std::ofstream output(filepath);

        if (!output.is_open())
        {
            return false;
        }

        output << sceneJson.dump(4);

        return true;
    }

    bool SceneSerializer::Deserialize(const std::filesystem::path &filepath)
    {
        std::ifstream input(filepath);

        if (!input.is_open())
        {
            return false;
        }

        json sceneJson;

        try
        {
            input >> sceneJson;
        }
        catch (const json::parse_error &)
        {
            return false;
        }

        if (!sceneJson.contains("entities") || !sceneJson["entities"].is_array())
        {
            return false;
        }

        m_scene.Clear();

        for (const auto &entityJson : sceneJson["entities"])
        {
            std::string name = "Entity";

            if (entityJson.contains("tag"))
            {
                name = entityJson["tag"].get<std::string>();
            }

            Entity entity = m_scene.CreateEntity(name);

            const EntityID entityID = entity.GetID();

            if (entityJson.contains("transform"))
            {
                const auto &transformJson = entityJson["transform"];
                auto &transform = m_scene.GetComponent<TransformComponent>(entityID);

                if (transformJson.contains("position"))
                {
                    const auto &position = transformJson["position"];

                    transform.transform.SetPosition(glm::vec3(position[0].get<float>(), position[1].get<float>(), position[2].get<float>()));
                }

                if (transformJson.contains("rotation"))
                {
                    const auto &rotation = transformJson["rotation"];

                    transform.transform.SetRotation(glm::vec3(rotation[0].get<float>(), rotation[1].get<float>(), rotation[2].get<float>()));
                }

                if (transformJson.contains("scale"))
                {
                    const auto &scale = transformJson["scale"];

                    transform.transform.SetScale(glm::vec3(scale[0].get<float>(), scale[1].get<float>(), scale[2].get<float>()));
                }
            }

            if (entityJson.contains("camera"))
            {
                const auto &cameraJson = entityJson["camera"];
                auto &camera = m_scene.AddComponent<CameraComponent>(entityID);

                if (cameraJson.contains("primary"))
                {
                    camera.primary = cameraJson["primary"].get<bool>();
                    if (cameraJson["type"].get<int>() == 0)
                    {
                        camera.projectionType = CameraProjectionType::Perspective;
                        camera.perspectiveNear = cameraJson["near"].get<float>();
                        camera.perspectiveFar = cameraJson["far"].get<float>();
                        camera.perspectiveFov = cameraJson["fov"].get<float>();
                    }
                    if (cameraJson["type"].get<int>() == 1)
                    {
                        camera.projectionType = CameraProjectionType::Orthographic;
                        camera.orthographicNear = cameraJson["near"].get<float>();
                        camera.orthographicFar = cameraJson["far"].get<float>();
                        camera.orthographicSize = cameraJson["size"].get<float>();
                    }
                }
            }
            if (entityJson.contains("rigidBody"))
            {
                const auto &rigidBodyJson = entityJson["rigidBody"];
                auto &rigidBody = m_scene.AddComponent<RigidBodyComponent>(entityID);
                if (rigidBodyJson.contains("mass"))
                {
                    rigidBody.mass = rigidBodyJson["mass"].get<float>();
                }
                if (rigidBodyJson.contains("useGravity"))
                {
                    rigidBody.useGravity = rigidBodyJson["useGravity"].get<bool>();
                }
            }
            if (entityJson.contains("boxCollider"))
            {
                const auto &boxCollJson = entityJson["boxCollider"];
                auto &boxColl = m_scene.AddComponent<BoxColliderComponent>(entityID);
                if (boxCollJson.contains("halfExtents"))
                {
                    const auto &halfExtents = boxCollJson["halfExtents"];
                    boxColl.halfExtends = glm::vec3(halfExtents[0].get<float>(), halfExtents[1].get<float>(), halfExtents[2].get<float>());
                }
                if (boxCollJson.contains("offset"))
                {
                    const auto &offset = boxCollJson["offset"];
                    boxColl.collider.offset = glm::vec3(offset[0].get<float>(), offset[1].get<float>(), offset[2].get<float>());
                }
                if (boxCollJson.contains("friction"))
                {
                    boxColl.collider.friction = boxCollJson["friction"].get<float>();
                }
                if (boxCollJson.contains("restitution"))
                {
                    boxColl.collider.restitution = boxCollJson["restitution"].get<float>();
                }
                if (boxCollJson.contains("isTrigger"))
                {
                    boxColl.collider.isTrigger = boxCollJson["isTrigger"].get<bool>();
                }
                if (boxCollJson.contains("enabled"))
                {
                    boxColl.collider.enabled = boxCollJson["enabled"].get<bool>();
                }
            }
            if (entityJson.contains("modelRenderer"))
            {
                const auto &modelRendererJson = entityJson["modelRenderer"];

                std::shared_ptr<Model> model;
                std::shared_ptr<Material> material;

                if (modelRendererJson.contains("model") && !modelRendererJson["model"].is_null())
                {
                    const std::string filepath = modelRendererJson["model"].get<std::string>();
                    model = m_resourceManager.Load<Model>(filepath);
                }

                if (modelRendererJson.contains("material") && !modelRendererJson["material"].is_null())
                {
                    const auto &materialJson = modelRendererJson["material"];

                    std::shared_ptr<Shader> shader;

                    if (materialJson.contains("shader") && !materialJson["shader"].is_null())
                    {
                        const std::string shaderPath = materialJson["shader"].get<std::string>();
                        shader = m_resourceManager.Load<Shader>(shaderPath);

                        if (shader)
                        {
                            material = std::make_shared<Material>(shader);

                            if (materialJson.contains("baseColor"))
                            {
                                const auto &baseColor = materialJson["baseColor"];
                                material->SetBaseColor(glm::vec4(
                                    baseColor[0].get<float>(),
                                    baseColor[1].get<float>(),
                                    baseColor[2].get<float>(),
                                    baseColor[3].get<float>()));
                            }
                            if (materialJson.contains("albedoTexture") && !materialJson["albedoTexture"].is_null())
                            {
                                const std::string texturePath = materialJson["albedoTexture"].get<std::string>();

                                auto texture = m_resourceManager.Load<Texture>(texturePath);
                                material->SetAlbedoTexture(texture);
                            }
                        }
                    }
                }
                m_scene.AddComponent<ModelRendererComponent>(entityID, model, material);
            }
        }

        return true;
    }
}