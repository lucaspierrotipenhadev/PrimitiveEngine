1. Serviços
- Serviços são objetos que existem durante praticamente toda a execução da Engine e executam trabalho continuamente.
- Eles possuem estado global da engine ou coordenam outros módulos.

- Lista de serviçes:
    Engine
    Renderer
    RenderAPI
    Window
    Input
    EventBus
    ResourceManager
    SceneManager
    PhysicsEngine
    AudioEngine
    ScriptEngine
    Time

- Características
    Criados durante a inicialização.
    Destruídos no encerramento da aplicação.
    Normalmente existe apenas uma instância.
    Não pertencem a nenhuma Scene.
    Não pertencem a nenhuma Entity.


2. Objetos de domínio
- Esses representam o mundo do jogo.
- São criados e destruídos conforme o jogo evolui.

- Lista de objetos de domínio:
    Scene
    Entity
    Component
    System
    Transform (não está definido ainda)
    Camera (não está definido ainda)
    MeshRenderer (não está definido ainda)
    SpriteRenderer (não está definido ainda)
    RigidBody (não está definido ainda)
    Collider (não está definido ainda)
    Animator (não está definido ainda)
    Light (não está definido ainda)
    Script (não está definido ainda)

- Hierarquia:
    Scene
    │
    ├── Entities
    │       │
    │       ├── Components
    │       └── Scripts
    │
    └── Systems


3. Recursos
- Esses dados são reutilizáveis.

- Lista de objetos de domínio:
    Texture (não está definido ainda)
    Mesh (não está definido ainda)
    Material (não está definido ainda)
    Shader (não está definido ainda)
    Model (não está definido ainda)
    Animation (não está definido ainda)
    AudioClip (não está definido ainda)
    Font (não está definido ainda)
    SceneAsset (não está definido ainda)
    Prefab (não está definido ainda)
    Skybox (não está definido ainda)
    Cubemap (não está definido ainda)
    ShaderProgram (não está definido ainda)


4. Objetos de infratestrutura
- São objetos que dão suporte ao funcionamento da engine.

- Lista de objetos de infraestrutura:
    FileSystem (não está definido ainda)
    Logger (não está definido ainda)
    Profiler (não está definido ainda)
    Configuration (não está definido ainda)
    UUID (não está definido ainda)
    Serializer (não está definido ainda)
    Deserializer (não está definido ainda)
    JobSystem (não está definido ainda)
    ThreadPool (não está definido ainda)
    MemoryAllocator (não está definido ainda)


5. Interfaces
- Lista de interfaces:
    IRenderAPI (não está definido ainda)
    IResourceLoader (não está definido ainda)
    ISerializer (não está definido ainda)
    IScript (não está definido ainda)
    IWindowBackend (não está definido ainda)
    IPhysicsBackend (não está definido ainda)


6. Backends
- Essas classes nunca aparecem para o usuário da engine.
- A API pública deverá trabalhar apenas com abstrações.

- Lista de backends:
    OpenGLRenderer
    SDLWindow
    SDLInput
    SDLAudio
    JsonSerializer


7. Objetos matemáticos
- Serão utilizados em praticamente todos os módulos
    Vector2
    Vector3
    Vector4
    Quaternion
    Matrix3
    Matrix4
    TransformMatrix
    Color
    Ray
    Plane
    BoundingBox
    BoundingSphere
    Frustum


8. Objetos gráficos
- Representam estados internos do renderer. (Não são assets)

- Lista  de objetos gráficos:
    Camera
    Viewport
    Framebuffer
    RenderTexture
    RenderTarget
    MaterialInstance
    VertexBuffer
    IndexBuffer
    VertexArray
    UniformBuffer