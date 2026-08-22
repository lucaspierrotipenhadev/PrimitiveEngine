struct TestComponent
{
    int value{0};

    explicit TestComponent(int initialValue)
        : value(initialValue)
    {
    }
};

/*TESTE DE VALIDAÇÃO
#include "Primitive/Scene/EntityID.hpp"
#include "Primitive/Scene/ComponentStorage.hpp"
#include "Primitive/Scene/Tests/TestComponent.hpp"

#include <iostream>
#include <cassert>

int main()
{
    primitive::ComponentStorage<TestComponent>
        storage;

    primitive::EntityID entity = 0;
    std::cout << "Iniciando testes...\n";

    auto &component = storage.Add(entity, 42);
    assert(component.value == 42);
    std::cout << "Add: valor definido corretamente\n";

    assert(storage.Has(entity));
    std::cout << "Has: componente encontrado\n";

    assert(storage.Size() == 1);
    std::cout << "Size: tamanho correto (1)\n";

    auto &retrieved = storage.Get(entity);
    assert(retrieved.value == 42);
    std::cout << "Get: valor recuperado corretamente\n";

    storage.Remove(entity);
    assert(!storage.Has(entity));
    std::cout << "Remove: componente removido\n";

    assert(storage.Size() == 0);
    std::cout << "Size: tamanho zero após remoção\n";

    std::cout << "\n✅ TODOS OS TESTES PASSARAM!\n";
    std::cin.get();
    return 0;
}*/

/*Teste de validação EntityManager
#include <cassert>
#include <iostream>

#include "Primitive/Scene/EntityManager.hpp"

int main()
{
    primitive::EntityManager manager;

    const auto entityA =
        manager.Create();

    const auto entityB =
        manager.Create();

    assert(entityA == 0);
    assert(entityB == 1);

    std::cout
        << "Create: IDs gerados corretamente\n";

    assert(manager.IsAlive(entityA));
    assert(manager.IsAlive(entityB));

    std::cout
        << "IsAlive: entidades vivas encontradas\n";

    assert(manager.GetAliveCount() == 2);

    std::cout
        << "Count: duas entidades vivas\n";

    manager.Destroy(entityA);

    assert(!manager.IsAlive(entityA));
    assert(manager.IsAlive(entityB));

    std::cout
        << "Destroy: entidade removida corretamente\n";

    assert(manager.GetAliveCount() == 1);

    manager.Clear();

    assert(manager.GetAliveCount() == 0);
    assert(!manager.IsAlive(entityB));

    std::cout
        << "Clear: todas as entidades removidas\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";
        std::cin.get();
}
*/

/*Teste do component manager

#include <cassert>
#include <iostream>

#include "Primitive/Scene/ComponentManager.hpp"

struct PositionComponent
{
    float x{0.0f};
    float y{0.0f};

    PositionComponent(
        float xValue,
        float yValue)
        : x(xValue),
          y(yValue)
    {
    }
};

struct HealthComponent
{
    int value{100};

    explicit HealthComponent(
        int initialValue)
        : value(initialValue)
    {
    }
};

int main()
{
    primitive::ComponentManager manager;

    const primitive::EntityID entityA = 0;
    const primitive::EntityID entityB = 1;

    auto& position =
        manager.Add<PositionComponent>(
            entityA,
            10.0f,
            20.0f
        );

    assert(position.x == 10.0f);
    assert(position.y == 20.0f);

    std::cout
        << "Add: PositionComponent adicionado\n";

    auto& health =
        manager.Add<HealthComponent>(
            entityA,
            75
        );

    assert(health.value == 75);

    std::cout
        << "Add: HealthComponent adicionado\n";

    assert(
        manager.Has<PositionComponent>(
            entityA
        )
    );

    assert(
        manager.Has<HealthComponent>(
            entityA
        )
    );

    assert(
        !manager.Has<PositionComponent>(
            entityB
        )
    );

    std::cout
        << "Has: componentes encontrados corretamente\n";

    auto& retrieved =
        manager.Get<PositionComponent>(
            entityA
        );

    assert(retrieved.x == 10.0f);
    assert(retrieved.y == 20.0f);

    std::cout
        << "Get: componente recuperado corretamente\n";

    manager.Remove<HealthComponent>(
        entityA
    );

    assert(
        !manager.Has<HealthComponent>(
            entityA
        )
    );

    assert(
        manager.Has<PositionComponent>(
            entityA
        )
    );

    std::cout
        << "Remove: somente o componente solicitado foi removido\n";

    manager.Add<HealthComponent>(
        entityA,
        50
    );

    manager.RemoveAll(entityA);

    assert(
        !manager.Has<PositionComponent>(
            entityA
        )
    );

    assert(
        !manager.Has<HealthComponent>(
            entityA
        )
    );

    std::cout
        << "RemoveAll: todos os componentes da entidade foram removidos\n";

    manager.Add<PositionComponent>(
        entityB,
        5.0f,
        10.0f
    );

    manager.Clear();

    assert(
        !manager.Has<PositionComponent>(
            entityB
        )
    );

    std::cout
        << "Clear: todos os storages removidos\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";
    std::cin.get();
}
*/

/*Teste do Scene
#include <cassert>
#include <iostream>

#include "Primitive/Scene/Scene.hpp"

int main()
{
    primitive::Scene scene;

    assert(scene.GetEntityCount() == 0);

    std::cout
        << "Initial: Scene vazia\n";

    auto entityA =
        scene.CreateEntity();

    auto entityB =
        scene.CreateEntity();

    assert(entityA.GetID() == 0);
    assert(entityB.GetID() == 1);

    assert(entityA.IsValid());
    assert(entityB.IsValid());

    assert(scene.GetEntityCount() == 2);

    std::cout
        << "CreateEntity: entidades criadas corretamente\n";

    assert(
        scene.IsEntityAlive(
            entityA.GetID()
        )
    );

    std::cout
        << "IsEntityAlive: entidade encontrada\n";

    scene.DestroyEntity(entityA);

    assert(!entityA.IsValid());
    assert(entityB.IsValid());

    assert(scene.GetEntityCount() == 1);

    std::cout
        << "DestroyEntity: entidade destruida corretamente\n";

    scene.Clear();

    assert(!entityB.IsValid());

    assert(scene.GetEntityCount() == 0);

    std::cout
        << "Clear: Scene limpa corretamente\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";
    
    std::cin.get();
}
*/

/*Teste facade Entity e Scene

struct PositionComponent
{
    float x{0.0f};
    float y{0.0f};

    PositionComponent(
        float xValue,
        float yValue)
        : x(xValue),
          y(yValue)
    {
    }
};

struct HealthComponent
{
    int value{100};

    explicit HealthComponent(
        int initialValue)
        : value(initialValue)
    {
    }
};

#include <cassert>
#include <iostream>

#include "Primitive/Scene/Scene.hpp"

int main()
{
    primitive::Scene scene;

    auto entity =
        scene.CreateEntity();

    assert(entity.IsValid());

    std::cout
        << "Entity: entidade valida\n";

    auto& position =
        entity.AddComponent<
            PositionComponent
        >(
            10.0f,
            20.0f
        );

    assert(position.x == 10.0f);
    assert(position.y == 20.0f);

    std::cout
        << "AddComponent: componente adicionado\n";

    assert(
        entity.HasComponent<
            PositionComponent
        >()
    );

    assert(
        !entity.HasComponent<
            HealthComponent
        >()
    );

    std::cout
        << "HasComponent: consulta correta\n";

    auto& retrieved =
        entity.GetComponent<
            PositionComponent
        >();

    assert(retrieved.x == 10.0f);
    assert(retrieved.y == 20.0f);

    std::cout
        << "GetComponent: componente recuperado\n";

    entity.AddComponent<
        HealthComponent
    >(75);

    assert(
        entity.HasComponent<
            HealthComponent
        >()
    );

    std::cout
        << "Multiple components: funcionamento correto\n";

    entity.RemoveComponent<
        PositionComponent
    >();

    assert(
        !entity.HasComponent<
            PositionComponent
        >()
    );

    assert(
        entity.HasComponent<
            HealthComponent
        >()
    );

    std::cout
        << "RemoveComponent: somente componente solicitado removido\n";

    scene.DestroyEntity(entity);

    assert(!entity.IsValid());

    assert(
        !entity.HasComponent<
            HealthComponent
        >()
    );

    std::cout
        << "DestroyEntity: facade tornou-se invalida\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";

    std::cin.get();
}*/

/*Teste do transform component
#include <cassert>
#include <iostream>

#include <glm/glm.hpp>

#include "Primitive/Scene/Scene.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"

int main()
{
    primitive::Scene scene;

    auto entity =
        scene.CreateEntity();

    auto& component =
        entity.AddComponent<
            primitive::TransformComponent
        >();

    assert(
        entity.HasComponent<
            primitive::TransformComponent
        >()
    );

    std::cout
        << "AddComponent: TransformComponent adicionado\n";

    component.transform.SetPosition(
        glm::vec3(
            1.0f,
            2.0f,
            3.0f
        )
    );

    component.transform.SetRotation(
        glm::vec3(
            10.0f,
            20.0f,
            30.0f
        )
    );

    component.transform.SetScale(
        glm::vec3(
            2.0f,
            2.0f,
            2.0f
        )
    );

    auto& retrieved =
        entity.GetComponent<
            primitive::TransformComponent
        >();

    assert(
        retrieved.transform.GetPosition()
        ==
        glm::vec3(
            1.0f,
            2.0f,
            3.0f
        )
    );

    assert(
        retrieved.transform.GetRotation()
        ==
        glm::vec3(
            10.0f,
            20.0f,
            30.0f
        )
    );

    assert(
        retrieved.transform.GetScale()
        ==
        glm::vec3(
            2.0f,
            2.0f,
            2.0f
        )
    );

    const glm::mat4 model =
        retrieved.transform.GetMatrix();

    std::cout
        << "Transform: dados recuperados corretamente\n";

    std::cout
        << "GetMatrix: matriz gerada corretamente\n";

    entity.RemoveComponent<
        primitive::TransformComponent
    >();

    assert(
        !entity.HasComponent<
            primitive::TransformComponent
        >()
    );

    std::cout
        << "RemoveComponent: TransformComponent removido\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";

    std::cin.get();
}*/

/* Teste do model renderer component
#include <cassert>
#include <iostream>
#include <memory>

#include "Primitive/Scene/Scene.hpp"
#include "Primitive/Scene/Components/ModelRendererComponent.hpp"
#include "Primitive/Scene/Components/TransformComponent.hpp"

#include "Primitive/Renderer/Model.hpp"
#include "Primitive/Renderer/Material.hpp"
#include "Primitive/Renderer/Shader.hpp"
#include "Primitive/Renderer/OpenGL/OpenGLShader.hpp"

std::shared_ptr<primitive::Model> model;
std::shared_ptr<primitive::Material> material;
std::shared_ptr<primitive::Shader> shader;

int main()
{
    primitive::Scene scene;

    shader = std::make_shared<primitive::OpenGLShader>("Assets/Shaders/basic.glsl", "// Vertex Shader Source Code...", 
        "// Fragment Shader Source Code...");
    model = std::make_shared<primitive::Model>("Assets/Models.cube.obj");
    material = std::make_shared<primitive::Material>(shader);

    auto entity = scene.CreateEntity();

    entity.AddComponent<primitive::TransformComponent>();

    std::cout << "Transform added!" <<std::endl;

    auto &renderer = entity.AddComponent<primitive::ModelRendererComponent>(
        model, material);

    assert(entity.HasComponent<primitive::ModelRendererComponent>());
    assert(renderer.model == model);
    assert(renderer.material == material);

    std::cout
        << "AddComponent: ModelRendererComponent adicionado." << std::endl;

    auto &retrieved =
        entity.GetComponent<
            primitive::ModelRendererComponent>();

    assert(retrieved.model == model);
    assert(retrieved.material == material);

    std::cout
        << "GetComponent: Model e Material recuperados corretamente\n";

    entity.RemoveComponent<
        primitive::ModelRendererComponent>();

    assert(
        !entity.HasComponent<
            primitive::ModelRendererComponent>());

    assert(
        entity.HasComponent<
            primitive::TransformComponent>());

    std::cout
        << "RemoveComponent: ModelRendererComponent removido\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";

    model.reset();
    material.reset();
    shader.reset();

    std::cin.get();
    return 0;
}
*/

/*Teste da camera component
#include <cassert>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Primitive/Scene/Scene.hpp"

#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/CameraComponent.hpp"

int main()
{
    primitive::Scene scene;

    auto cameraEntity =
        scene.CreateEntity();

    auto& transform =
        cameraEntity.AddComponent<
            primitive::TransformComponent
        >();

    transform.transform.SetPosition(
        glm::vec3(
            0.0f,
            0.0f,
            3.0f
        )
    );

    const float aspectRatio =
        1280.0f / 720.0f;

    primitive::Camera camera;

    camera.SetProjection(
        glm::perspective(
            glm::radians(45.0f),
            aspectRatio,
            0.1f,
            100.0f
        )
    );

    auto& cameraComponent =
        cameraEntity.AddComponent<
            primitive::CameraComponent
        >(
            std::move(camera),
            true
        );

    assert(
        cameraEntity.HasComponent<
            primitive::TransformComponent
        >()
    );

    assert(
        cameraEntity.HasComponent<
            primitive::CameraComponent
        >()
    );

    std::cout
        << "Components: Transform + Camera adicionados\n";

    assert(cameraComponent.primary);

    std::cout
        << "Primary: Camera marcada como principal\n";

    const glm::mat4 view =
        glm::inverse(
            transform.transform.GetMatrix()
        );

    const glm::mat4 projection =
        cameraComponent.camera.GetProjection();

    (void)view;
    (void)projection;

    std::cout
        << "Matrices: View e Projection obtidas corretamente\n";

    cameraEntity.RemoveComponent<
        primitive::CameraComponent
    >();

    assert(
        !cameraEntity.HasComponent<
            primitive::CameraComponent
        >()
    );

    assert(
        cameraEntity.HasComponent<
            primitive::TransformComponent
        >()
    );

    std::cout
        << "RemoveComponent: CameraComponent removido\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";
    
    std::cin.get();
}
*/

/*Teste do Scene update
#include <cassert>
#include <iostream>

#include "Primitive/Scene/Scene.hpp"

#include "Primitive/Scene/Components/TransformComponent.hpp"
#include "Primitive/Scene/Components/CameraComponent.hpp"

int main()
{
    primitive::Scene scene;

    auto entityA =
        scene.CreateEntity();

    auto entityB =
        scene.CreateEntity();

    auto entityC =
        scene.CreateEntity();

    entityA.AddComponent<
        primitive::TransformComponent
    >();

    entityB.AddComponent<
        primitive::TransformComponent
    >();

    entityB.AddComponent<
        primitive::CameraComponent
    >();

    entityC.AddComponent<
        primitive::CameraComponent
    >();

    std::size_t transformCount = 0;

    scene.ForEach<
        primitive::TransformComponent
    >(
        [&transformCount](
            primitive::EntityID,
            primitive::TransformComponent&)
        {
            ++transformCount;
        }
    );

    assert(transformCount == 2);

    std::cout
        << "ForEach<Transform>: 2 entidades encontradas\n";

    std::size_t cameraCount = 0;

    scene.ForEach<
        primitive::CameraComponent
    >(
        [&cameraCount](
            primitive::EntityID,
            primitive::CameraComponent&)
        {
            ++cameraCount;
        }
    );

    assert(cameraCount == 2);

    std::cout
        << "ForEach<Camera>: 2 entidades encontradas\n";

    std::size_t combinedCount = 0;

    scene.ForEach<
        primitive::TransformComponent,
        primitive::CameraComponent
    >(
        [&combinedCount](
            primitive::EntityID,
            primitive::TransformComponent&,
            primitive::CameraComponent&)
        {
            ++combinedCount;
        }
    );

    assert(combinedCount == 1);

    std::cout
        << "ForEach<Transform, Camera>: 1 entidade encontrada\n";

    scene.Update(1.0f / 60.0f);

    assert(scene.GetEntityCount() == 3);

    std::cout
        << "Update: Scene atualizada corretamente\n";

    std::cout
        << "\nTODOS OS TESTES PASSARAM!\n";

    std::cin.get();
}
*/