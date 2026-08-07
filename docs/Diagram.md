Application
      │
      ▼
Engine
      │
      ├─────────────┐
      ▼             ▼
    Renderer      SceneManager
      │             │
      ▼             ▼
    RenderAPI      Scene
      │             │
      ▼             ▼
    IRendererAPI   ECS (EntityManager->ComponentManager->SystemManager)
      │
      ▼
    OpenGL, DirectX, Vulcan
      │
      ▼
      SDL3