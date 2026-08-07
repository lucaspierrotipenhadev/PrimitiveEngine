1. Engine
- Responsabilidade:
    Coordenar todos os módulos da engine.

- Depende de:
    Renderer
    SceneManager
    ResourceManager
    PhysicsEngine
    AudioEngine
    Input
    Window
    Time
    EventBus
    ScriptEngine

- É utilizado por:
    Application

- Não deve depender de:
    OpenGL
    SDL
    Scripts do usuário
    
    
2. Renderer
- Responsabilidade:
    Controlar toda a renderização da engine.

- Depende de:
    RenderAPI
    Camera
    Mesh
    Material
    Shader

- É utilizado por:
    Engine

- Não deve depender de:
    Physics
    Audio
    ECS


3. RenderAPI
- Responsabilidade:
    Fornecer uma interface única para qualquer API gráfica.

- Depende de:
    IRenderAPI (O renderer não deve saber da existência da biblioteca, ex: OpenGL, DirectX, etc)

- É utilizado por:
    Renderer
    Não deve depender de
    Scene
    Physics


4. Window
- Responsabilidade:
    Criar e gerenciar a janela da aplicação.
    Gerenciar contexto gráfico.
    Troca de buffers.
    Fullscreen.
    VSync.

- Depende de:
    SDL3

- É utilizado por:
    Engine

4. Input
- Responsabilidade:
    Abstrair teclado, mouse e gamepads.
    Converter eventos do SDL em eventos da engine.

- Depende de:
    EventBus

- É utilizado por:
    Scripts
    Engine
    Editor

- Não deve depender de:
    Renderer


5. EventBus
-Responsabilidade:
    Distribuir eventos entre os módulos.
    
- Depende de:
    Nenhum módulo da engine.

- É utilizado por:
    Todos os sistemas.


6. ResourceManager
- Responsabilidade:
    Gerenciar todos os recursos carregados.
    Texturas.
    Modelos.
    Shaders.
    Áudios.
    Fontes.

- Depende de:
    Filesystem

- É utilizado por:
    Renderer
    Audio
    Physics


7. SceneManager
- Responsabilidade:
    Criar.
    Carregar.
    Salvar.
    Trocar cenas.

- Depende de:
    Scene

- É utilizado por:
    Engine


8. Scene
- Responsabilidade:
    Representar um mundo.
    Armazenar entidades.
    Executar Systems.

- Depende de:
    Entity
    ECS

- É utilizada por:
    SceneManager


9. Entity
- Responsabilidade:
    Representar um objeto do mundo.

- Depende de:
    Components

- É utilizada por
    Scene


9. Components
- Responsabilidade:
    Armazenar apenas dados.

- Depende de:
    Nenhum sistema.

- É utilizado por:
    Entity
    Systems


10. System
- Responsabilidade:
    Processar componentes.
    Nunca armazenar estado permanente.

- Depende de:
    Components

- É utilizado por:
    Scene


11. PhysicsEngine
- Responsabilidade:
    Executar toda a simulação física.

- Depende de:
    BroadPhase
    NarrowPhase
    CollisionSolver

- É utilizado por:
    Engine


12. AudioEngine
- Responsabilidade:
    Gerenciar sons e músicas.

- Depende de:
    SDL3 Audio

- É utilizado por:
    Engine


13. ScriptEngine
- Responsabilidade:
    Executar scripts da engine.
    Gerenciar ciclo de vida dos scripts.

- Depende de:
    Scene
    Entity

- É utilizado por:
    Engine


14. Time
- Responsabilidade:
    Fornecer deltaTime.
    FPS.
    Tempo acumulado.
    Temporizadores.

- Depende de:
    SDL3 Timer

- É utilizado por:
    Praticamente todos os sistemas.


15. IRendererAPI
- Responsabilidade:
    Fornecer a implementação concreta para a interface, seja OpenGL, DirectX, ou Vulcan

- Depende de:
    Backend

- é utilizado por:
    RenderAPI