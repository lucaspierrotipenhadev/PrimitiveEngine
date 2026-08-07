1. Application
- Cria:
    Engine

- Destrói:
    Engine


2. Engine
- Cria:
    Window
    Renderer
    Input
    SceneManager
    ResourceManager
    Audio
    Physics
    Time
    EventBus
    ScriptEngine

- Destrói:
    Window
    Renderer
    Input
    SceneManager
    ResourceManager
    Audio
    Physics
    Time
    EventBus
    ScriptEngine


3. SceneManager
- Cria:
    Scene

- Destrói:
    Scene


4. Scene
- Cria:
    Entities

- Destrói:
    Entities


5. Entity
- Cria:
    Components

- Destrói:
    Components


6. ResourceManager
- Cria:
    Texture
    Shader
    Material
    Mesh
    AudioClip
    Animation

- Destrói:
    Texture
    Shader
    Material
    Mesh
    AudioClip
    Animation


7. Renderer
- Cria:
    Nunca deve criar recursos.
    Deve apenas usar recursos criados pelo ResourceManager


8. Physics
- Cria:
    Nunca cria entities, nem components.
    Apenas processa


9. Systems
- Cria:
    Nunca cria components, entities.
    Apenas opera components e entities.