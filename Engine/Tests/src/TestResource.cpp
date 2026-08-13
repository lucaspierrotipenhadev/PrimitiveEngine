/*#include <cassert>
#include <iostream>

#include "Primitive/Resources/ResourceManager.hpp"
#include "Primitive/Tests/TestResource.hpp"

int main()
{
    using namespace primitive;

    std::cout << "=== ResourceManager Test ===\n\n";

    ResourceManager manager;

    // --------------------------------------------------
    // TESTE 1 - Load
    // --------------------------------------------------

    auto resource =
        manager.Load<TestResource>("assets/test.asset");

    assert(resource != nullptr);

    std::cout << "[OK] Load criou o recurso.\n";


    // --------------------------------------------------
    // TESTE 2 - Get
    // --------------------------------------------------

    auto loadedResource =
        manager.Get<TestResource>("assets/test.asset");

    assert(loadedResource != nullptr);

    std::cout << "[OK] Get encontrou o recurso.\n";


    // --------------------------------------------------
    // TESTE 3 - Cache
    // --------------------------------------------------

    auto resourceAgain =
        manager.Load<TestResource>("assets/test.asset");

    assert(resourceAgain != nullptr);

    assert(resource == resourceAgain);

    std::cout << "[OK] Cache retornou a mesma instancia.\n";


    // --------------------------------------------------
    // TESTE 4 - Filepath
    // --------------------------------------------------

    assert(
        resource->GetFilepath() ==
        "assets/test.asset"
    );

    std::cout << "[OK] Filepath armazenado corretamente.\n";


    // --------------------------------------------------
    // TESTE 5 - Recurso inexistente
    // --------------------------------------------------

    auto missing =
        manager.Get<TestResource>("assets/does_not_exist.asset");

    assert(missing == nullptr);

    std::cout << "[OK] Recurso inexistente retorna nullptr.\n";


    std::cout << "\n=== Todos os testes passaram! ===\n";
    std::cin.get();

    return 0;
}*/