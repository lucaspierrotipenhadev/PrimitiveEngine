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