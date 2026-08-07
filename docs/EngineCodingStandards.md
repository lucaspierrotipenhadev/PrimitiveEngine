1. Objetivo

Este documento define os padrões de desenvolvimento da Primitive Engine.

Todos os módulos da engine deverão seguir estas regras para garantir:

Consistência;
Legibilidade;
Manutenibilidade;
Baixo acoplamento;
Alta coesão;
Facilidade de testes.

Nenhuma implementação poderá violar estas regras sem justificativa técnica documentada em um ADR.

2. Filosofia

Toda implementação deverá seguir os seguintes princípios:

A simplicidade é preferível à complexidade.
O código deve ser legível antes de ser inteligente.
Cada classe deve possuir apenas uma responsabilidade.
A API pública deve esconder detalhes internos.
O usuário nunca deverá conhecer SDL, OpenGL ou qualquer backend.
Todo recurso deverá possuir um único responsável pelo seu ciclo de vida.
O código deve ser escrito pensando em manutenção de longo prazo.
3. Organização do projeto
PrimitiveEngine/

├── Engine/
│   ├── include/
│   └── src/
│
├── Editor/
│
├── Sandbox/
│
├── Tests/
│
├── ThirdParty/
│
├── Assets/
│
├── Docs/
│
└── CMakeLists.txt
4. Organização dos módulos

Cada módulo seguirá exatamente a mesma estrutura.

Renderer/

include/
    Primitive/
        Renderer/
            Renderer.hpp
            Camera.hpp
            Shader.hpp

src/
    Renderer.cpp
    Camera.cpp
    Shader.cpp

Nunca haverá implementação dentro da pasta include.

5. Convenções de nomenclatura
Classes

Sempre PascalCase.

class Renderer;
class ResourceManager;
class PhysicsEngine;
Interfaces

Sempre iniciadas por I.

class IRenderAPI;
class ISerializer;
class IScript;
Estruturas

PascalCase.

struct Vertex;
struct Transform;
Arquivos

Mesmo nome da classe.

Renderer.hpp
Renderer.cpp

Scene.hpp
Scene.cpp
Namespaces

Minúsculos.

namespace primitive
{

}

ou, caso prefira separar módulos:

namespace primitive::renderer
{

}
Métodos

Sempre PascalCase.

Initialize()

Shutdown()

CreateScene()

LoadTexture()

DrawMesh()
Variáveis

camelCase.

deltaTime

windowWidth

mainCamera
Variáveis privadas

Prefixo m_.

m_window

m_renderer

m_sceneManager
Parâmetros

camelCase.

CreateEntity(const std::string& name)
Constantes

SCREAMING_SNAKE_CASE.

MAX_LIGHTS

DEFAULT_FOV

MAX_TEXTURE_SLOTS
Enums

Sempre enum class.

enum class Key
{
    W,
    A,
    S,
    D
};

Nunca utilizar enum tradicional.

6. Includes

Sempre nesta ordem.

// Próprio header
#include "Renderer.hpp"

// STL
#include <memory>
#include <vector>

// Terceiros
#include <SDL3/SDL.h>

// Engine
#include "Scene.hpp"
7. Memória

A Primitive Engine utilizará RAII em 100% do projeto.

É proibido:

new

delete

exceto em locais específicos da infraestrutura.

Ponteiros
Preferência
stack

↓

unique_ptr

↓

shared_ptr

↓

weak_ptr

A ordem acima deverá ser respeitada.

unique_ptr

Sempre que existir apenas um dono.

std::unique_ptr<Renderer>
shared_ptr

Somente quando houver múltiplos proprietários legítimos.

Nunca usar por conveniência.

weak_ptr

Sempre que existir referência não proprietária.

8. Tratamento de erros

Nunca retornar códigos numéricos.

Evitar:

return -1;

Preferir:

throw EngineException(...)

ou

Expected<T>

Dependendo da política adotada.

Essa decisão deverá ser uniforme em toda a engine.

9. Comentários

Comentários devem explicar por que, e não o que.

Ruim:

// Incrementa x

x++;

Bom:

// Evita perda de precisão durante a integração física.
10. Documentação

Toda classe pública deverá possuir documentação.

Exemplo:

/**
 * Responsável pela renderização da cena.
 */
class Renderer
{

};
11. Arquivos

Uma classe pública por arquivo.

Nunca:

Renderer.hpp

Camera

Mesh

Texture

Material

Cada classe terá seu próprio arquivo.

12. Dependências

É proibido:

Renderer

↓

Physics

↓

Renderer

Dependências circulares nunca serão aceitas.

13. Backend

SDL.

OpenGL.

OpenAL.

Nunca poderão aparecer fora do backend.

O restante da engine conhecerá apenas interfaces.

14. Eventos

Todos os módulos deverão comunicar-se através do EventBus quando apropriado.

Evitar chamadas diretas entre módulos independentes.

15. ECS

Os Components conterão apenas dados.

Nunca possuirão lógica.

Exemplo correto:

struct Transform
{
    Vector3 position;
    Quaternion rotation;
};
16. Systems

Os Systems nunca armazenarão estado permanente.

Eles apenas processam Components.

17. Recursos

Todos os Assets deverão ser carregados exclusivamente pelo ResourceManager.

Nunca:

Texture texture("grass.png");

Sempre:

auto texture = Resources::Load<Texture>("grass.png");
18. Performance

Prioridades:

Corretude

↓

Legibilidade

↓

Arquitetura

↓

Performance

Otimizações prematuras deverão ser evitadas.

Toda otimização deverá ser baseada em medições (profiling).

19. Testes

Todo módulo deverá possuir testes unitários sempre que possível.

Estrutura:

Tests/

Core/

Renderer/

Math/

Physics/

ECS/
20. Logging

Nunca utilizar:

std::cout

Sempre:

Logger::Info()

Logger::Warning()

Logger::Error()

Logger::Critical()
21. Controle de versão

Cada alteração significativa deverá:

Compilar sem erros.
Passar pelos testes existentes.
Manter a documentação atualizada quando alterar a arquitetura.
Ser acompanhada por um ADR quando introduzir uma decisão arquitetural relevante.
22. Princípios de arquitetura

Todo código da Primitive Engine deverá respeitar:

Single Responsibility Principle (SRP)
Open/Closed Principle (OCP)
Liskov Substitution Principle (LSP)
Interface Segregation Principle (ISP)
Dependency Inversion Principle (DIP)

Além disso:

Alta coesão
Baixo acoplamento
RAII
ECS
Data-Oriented Design (onde fizer sentido)
Composition over Inheritance
Program to Interfaces
23. Checklist para Pull Requests

Antes de considerar uma funcionalidade concluída, verifique:

 O código segue as convenções de nomenclatura?
 A nova classe tem apenas uma responsabilidade?
 Não há dependências circulares?
 O ownership está claramente definido?
 O ciclo de vida dos objetos respeita RAII?
 Não foram utilizados new/delete diretamente?
 Há documentação para a API pública?
 Existem testes para a nova funcionalidade (quando aplicável)?
 A implementação mantém a compatibilidade com a arquitetura definida?
 Foi necessário criar ou atualizar um ADR?