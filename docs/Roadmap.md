| Versão | Demonstração                               |
| ------ | ------------------------------------------ |
| v0.1   | Janela + Game Loop + Tela limpa            |
| v0.2   | Triângulo renderizado                      |
| v0.3   | Cubo 3D com câmera                         |
| v0.4   | ECS movimentando entidades                 |
| v0.5   | Carregamento de modelos (`.obj` ou `.fbx`) |
| v0.6   | Colisão física simples                     |
| v0.7   | Cena serializada                           |
| v0.8   | Editor básico                              |
| v1.0   | Pequeno jogo de demonstração               |


v0.1 — Foundation

| Componente                  | Estado |
| --------------------------- | ------ |
| Core / Application / Engine | ✅      |
| Logger                      | ✅      |
| Time                        | ✅      |
| Window                      | ✅      |
| Platform                    | ✅      |
| SDL3                        | ✅      |
| Input                       | ✅      |
| SDLInput                    | ✅      |
| EventBus                    | ✅      |
| Resource                    | ✅      |
| ResourceManager             | ✅      |
| FileSystem                  | ✅      |
| IResourceLoader             | ✅      |
| LoaderRegistry              | ✅      |
| Configuration               | ✅      |
| Configuration → Window      | ✅      |
| Configuration → Engine      | ✅      |
| Core Integration Test       | ✅      |


v.02
| Componente             | Estado |
| ---------------------- | ------ |
| Renderer               | ✅      |
| IRendererAPI           | ✅      |
| TestRendererAPI        | ✅      |
| OpenGLRenderer         | ✅      |
| OpenGL Context         | ✅      |
| GLAD 2                 | ✅      |
| OpenGL 4.6 Core        | ✅      |
| Renderer → Engine      | ✅      |
| Clear / primeiro frame | ✅      |
| Shader                 | ✅      |
| Camera                 | ✅      |
| Material               | ✅      |
| Texture                | ✅      |
| Mesh                   | ✅      |
| Model                  | ✅      |

v.03

Milestone 3 — Scene / ECS

1. Entity ID
2. Component base / storage
3. EntityManager
4. ComponentManager
5. Entity facade
6. Scene
7. TransformComponent
8. ModelRendererComponent
9. CameraComponent
10. Scene Update
11. Scene Render
12. remover m_test* do Engine