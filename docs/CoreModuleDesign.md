1. Objetivo
- O módulo Core contém toda a infraestrutura necessária para o funcionamento da Primitive Engine.
- Ele não possui conhecimento sobre renderização, física ou ECS.
- Sua responsabilidade é fornecer os serviços fundamentais utilizados por todos os demais módulos.


2. Princípios
    O Core nunca dependerá de Renderer, Physics ou ECS.
    Todos os módulos da engine poderão depender do Core.
    O Core deverá ser totalmente desacoplado das APIs gráficas.
    O Core deverá utilizar RAII em todos os recursos.
    O Core deverá ser facilmente testável.


3. Estrutura do módulo

Core/
│
├── Application
├── Engine
├── Configuration
├── Logger
├── FileSystem
├── Time
├── EventBus
├── UUID
├── Layer
├── LayerStack
├── CommandLine
└── Version
Platform/
├── Window
└── Input


4. Responsabilidade de cada classe
- Representar a aplicação do usuário. É o ponto de entrada da engine.
- Responsabilidades:
    Criar engine;
    Executar engine;
    encerrar engine.
- Nunca deve conhcer:
    Opengl, DirectX, Vulcan, sdl, physics, renderer.


5. Engine
- Coordenar todos os serviços da Engine.
- Responsabilidades:
Inicialização
    Game Loop
    Shutdown
    Gerenciar módulos
- Dono de:
    Renderer
    Window
    Input
    EventBus
    ResourceManager
    PhysicsEngine
    AudioEngine
    SceneManager


6. Configuration
- Ela armazenará todas as configurações.
Exemplo:
-----------------------------------------------------------
Window Width
Window Height
Fullscreen
VSync
Renderer Backend
Asset Path
Project Path
Fixed TimeStep
Max FPS
Audio Volume
-----------------------------------------------------------
Deverá algum tipo de arquivo como:
-----------------------------------------
window:
  width: 1280
  height: 720

renderer:
  backend: OpenGL

physics:
  fixedStep: 0.016666
-----------------------------------------


7. Logger
- Será utilizado por toda a Engine.
API imaginada:
-----------------------------------------------------
Logger::Info("Renderer initialized");

Logger::Warning("Texture not found");

Logger::Error("Shader compilation failed");

Logger::Critical("Renderer crashed");
-----------------------------------------------------

- No futuro, poderá escrever tanto no console quanto em arquivos de log.


8. FileSystem
- Essa classe centralizará o acesso ao sistema de arquivos.
- Nunca chamaremos std::filesystem diretamente fora dela.

Exemplo:
-----------------------------------------------------
FileSystem::Exists(path);

FileSystem::ReadFile(path);

FileSystem::WriteFile(path);

FileSystem::CreateDirectory(path);
-----------------------------------------------------
Isso facilita testes e futuras adaptações.


9. Window
- Responsável por:
    criar a janela;
    destruir a janela;
    trocar buffers;
    alterar resolução;
    fullscreen;
    cursor;
    título.

Nunca desenha nada.


10. Time

Fornece:
-----------------------------------------------------
Time::DeltaTime();

Time::FPS();

Time::Elapsed();

Time::FixedDeltaTime();
-----------------------------------------------------
O restante da engine apenas consulta esses valores.


11. EventBus
- Responsável por distribuir eventos entre módulos. Eventos como:
    WindowResizeEvent
    KeyPressedEvent
    MouseMovedEvent
    SceneLoadedEvent
    EntityCreatedEvent
    CollisionEvent


12. Input
- Responsável por abstrair SDL.

Exemplo:
-----------------------------------------------------
Input::IsKeyPressed(Key::W);

Input::MousePosition();

Input::IsMouseButtonPressed(MouseButton::Left);
-----------------------------------------------------
Observe que a API nunca expõe SDL_Keycode.


13. UUID
- Toda Entity terá um identificador único. Provavelmente:
    using UUID = uint64_t;
    Ou uma classe própria.

    Isso será importante para serialização e referências entre objetos.


14. Layer
- Aqui proponho uma pequena diferença em relação ao seu projeto original.
- Inspirado na arquitetura da Hazel, podemos ter camadas de execução.

Por exemplo:

Engine Layer
↓
Editor Layer
↓
Game Layer
↓
ImGui Layer

Cada Layer recebe:
    OnAttach()
    OnDetach()
    OnUpdate()
    OnEvent()
    OnRender()

    Isso facilita muito a integração do Editor no futuro.


15. LayerStack
- Gerencia todas as Layers.
- API imaginada:
    PushLayer();
    PopLayer();
    PushOverlay();
    PopOverlay();

16. CommandLine
- Encapsula os argumentos recebidos no main. Exemplo:
    --project Sandbox
    --renderer OpenGL
    --fullscreen
    --vsync

    Assim, a Application pode acessar esses parâmetros de forma estruturada.


17. Version
- Centraliza informações da versão da engine.

-----------------
Primitive Engine

Version 0.1.0

Renderer OpenGL

Build Debug

Build Date
---------------

Útil tanto para logs quanto para o Editor.

18. Dependências
-Application
        │
        ▼
     Engine
        │
        ├────────────┐
        ▼            ▼
     Window     Configuration
        │
        ▼
      Input
        │
        ▼
    EventBus
-Time
-Logger
-FileSystem
-UUID
-LayerStack

Todos os outros módulos dependerão apenas desse conjunto de serviços.

19. Ordem de inicialização
Logger
↓
Configuration
↓
FileSystem
↓
Window
↓
Input
↓
EventBus
↓
Time
↓
LayerStack
↓
Engine Ready

O Renderer, ResourceManager, PhysicsEngine e os demais módulos serão inicializados posteriormente pela própria Engine, utilizando esses serviços.