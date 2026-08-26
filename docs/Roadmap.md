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


Milestone 1 Engine e Resource

1. Core / Application / Engine 
2. Logger                      
3. Time                        
4. Window                      
5. Platform                    
6. SDL3                        
7. Input                       
8. SDLInput                    
9. EventBus                    
10. Resource                   
11. ResourceManager            
12. FileSystem                 
13. IResourceLoader            
14. LoaderRegistry             
15. Configuration              
16. Configuration → Window     
17. Configuration → Engine     
18. Core Integration Test      

Milestone 2 - Renderer e camera
1. Renderer               
2. IRendererAPI           
3. TestRendererAPI        
4. OpenGLRenderer         
5. OpenGL Context        
6. GLAD 2                 
7. OpenGL 4.6 Core        
8. Renderer → Engine      
9. Clear / primeiro frame 
10. Shader                 
11. Camera                 
12. Material               
13. Texture                
14. Mesh                   
15. Model                  

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

Milestone 4 — Physics

1. Physics module / arquitetura
2. RigidbodyComponent
3. Collider base
4. BoxColliderComponent
5. SphereColliderComponent
6. PhysicsWorld
7. integração Scene → PhysicsWorld
8. integração Transform ↔ Rigidbody
9. AABB / bounding volumes
10. Broad Phase
11. Narrow Phase
12. Collision detection
13. Collision events
14. Collision response simples
15. Fixed timestep
16. Scene Update + Physics
17. teste visual com entidades

Milestone 5 — Editor

1. Editor module / arquitetura
2. ImGui integration
3. Editor application
4. Dockspace principal
5. Hierarchy panel
6. Entity selection
7. Inspector panel
8. edição de TransformComponent
9. edição de CameraComponent
10. edição de ModelRendererComponent
11. edição de RigidbodyComponent
12. edição de Box/Sphere Collider
13. Scene viewport 
14. render target / framebuffer
15. viewport resize
16. gizmos de Transform <----------------------------- Parado aqui
17. criação e remoção de entidades
18. adicionar/remover componentes
19. Play / Stop mode
20. cena de edição vs cena em runtime
21. salvar/carregar Scene
22. primeiro fluxo completo no Editor