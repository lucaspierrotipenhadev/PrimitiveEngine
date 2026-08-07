1. Objetivo
- O objetivo aqui é definir de forma precisa, os fluxos de inicialização, execução e encerramento da Primitive engine.
- Toda implementação deverá seguir exatamente esta sequência, garantindo que os módulos sejam inicializados e finalizados na ordem correta.


2. Fluxo geral
- Observe que nenhum serviço é utilizado antes de ser inicializado.

main()
    │
    ▼
Application
    │
    ▼
Engine
    │
    ▼
Initialize()
    │
    ▼
Load Services
    │
    ▼
Load Resources
    │
    ▼
Load First Scene
    │
    ▼
Start()
    │
    ▼
Main Loop
    │
    ▼
Shutdown()


3. Boot Sequence

3.1 Etapa 1 - main()
- Oprograma inicia

--------------------------------------
int main()
{
    Primitive::Application app("Sandbox");

    app.Run();
}
--------------------------------------

- Responsabilidade:
    Criar a aplicação.
    Delegar toda a execução para ela. (Nada além disso)

3.2 Etapa 2 - Application
- Responsabilidade:
    cria a Engine;
    lê configurações iniciais;
    chama a Engine.Initialize().

Application
↓
Create Engine
↓
Initialize Engine
↓
Run()
↓
Shutdown()

3.3 Etapa 3 - Engine::initialize()

- A engine inicializa os serviços ( a ordem é importante, pois cada um dos serviços, precisam dos serviços anteriores)

Logger
↓
Configuration
↓
FileSystem
↓
Window
↓
IRenderAPI
↓
Renderer
↓
Input
↓
EventBus
↓
Time
↓
ResourceManager
↓
PhysicsEngine
↓
AudioEngine
↓
ScriptEngine
↓
SceneManager


4. Criação da janela

Window.Initialize()
↓
SDL_Init()
↓
Create Window
↓
Create Graphics Context
↓
Initialize OpenGL

Após isso: window ready


5. Inicialização do render

Renderer.Initialize()
↓
Create IRenderAPI
↓
Initialize Backend
↓
Create Default Shader
↓
Create Default Material
↓
Create Default Camera

Ao final: Renderer ready


6. ResourceManager

ResourceManager.Initialize()
↓
Create Asset Cache
↓
Register Resource Loaders
↓
Load Default Assets

Exemplo:

----------------------------------
Default Shader
White Texture
Default Material
Cube Mesh
Sphere Mesh
----------------------------------


7. SceneManager

SceneManager.Initialize()
↓
Create Empty Scene
↓
Set Active Scene

Obs.: Ainda não existe nenhuma Entity


8. Carregamento da primeira cena

Load Scene
↓
Deserialize Scene
↓
Create Entities
↓
Create Components
↓
Resolve Assets
↓
Instantiate Scripts
↓
Scene Ready


9. Inicialização dos scripts

- Agora todos os scripts recebem: OnCreate(), depois OnStart() apenas uma vez.


10. Engine ready

- Agora a engine entra no Game Loop, nesta ordem:

Poll Window Events
↓
Dispatch EventBus
↓
Update Input
↓
Update Time
↓
Run FixedUpdate
↓
Physics Simulation
↓
Collision Events
↓
Animation Update
↓
Script Update
↓
Scene Update
↓
Renderer
↓
Audio
↓
Swap Buffers


11. Fixed Update
- Ocorre apenas quando necessário

Accumulator >= Fixed Time Step
↓
Run Physics
↓
Run Fixed Scripts


12. Render Frame

Clear Buffers
↓
Collect Renderables
↓
Sort Draw Calls
↓
Render Opaque
↓
Render Transparent
↓
Render UI
↓
Swap Buffers


13. Shutdown

Stop Scripts
↓
Destroy Scene
↓
Unload Resources
↓
Shutdown Renderer
↓
Destroy Window
↓
Shutdown SDL
↓
Destroy Engine
↓
Destroy Application


14. Ordem de destruição

Scripts
↓
Entities
↓
Components
↓
Scene
↓
SceneManager
↓
ResourceManager
↓
Renderer
↓
Window
↓
Engine
↓
Application


15. Estados da engine

--------------------------------
enum class EngineState
{
    Uninitialized,
    Initializing,
    Running,
    Paused,
    ShuttingDown,
    Stopped
};
--------------------------------

- Cada módulo poderá consultar esse estado quando necessário, e isso evita chamadas inválidas (como tentar carregar uma cena antes da inicialização).


16. Fluxo completo
- Este diagrama resume toda a vida da aplicação:

main()
    │
    ▼
Application
    │
    ▼
Engine
    │
    ▼
Initialize
    │
    ├── Logger
    ├── Configuration
    ├── FileSystem
    ├── Window
    ├── IRenderAPI
    ├── Renderer
    ├── Input
    ├── EventBus
    ├── Time
    ├── ResourceManager
    ├── PhysicsEngine
    ├── AudioEngine
    ├── ScriptEngine
    └── SceneManager
    │
    ▼
Load Scene
    │
    ▼
Instantiate Entities
    │
    ▼
Instantiate Components
    │
    ▼
OnCreate()
    │
    ▼
OnStart()
    │
    ▼
Main Loop
    │
    ├── Poll Events
    ├── Input
    ├── Time
    ├── FixedUpdate
    ├── Physics
    ├── Animation
    ├── Scripts
    ├── Scene Update
    ├── Render
    ├── Audio
    └── Swap Buffers
    │
    ▼
Shutdown