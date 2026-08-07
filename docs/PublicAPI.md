1. Filosofia da API
- A API pública da Primitive Engine deve esconder completamente os detalhes de implementação da engine. O usuário nunca deverá interagir diretamente com SDL, OpenGL ou qualquer backend específico. Todas as funcionalidades serão expostas através de uma interface simples, consistente e orientada a objetos.


2. Criação da aplicação
- Será o menor programa possível:

--------------------------------------------------------
#include <Primitive/Application.hpp>

using namespace Primitive;

int main()
{
    Application app("Primitive Sandbox");

    app.Run();
}
--------------------------------------------------------

3. Criação da cena:

--------------------------------------------------------
Application app("Sandbox");

Scene& scene = app.CreateScene("Main Scene");
--------------------------------------------------------
- Depois
--------------------------------------------------------
app.SetActiveScene(scene);
--------------------------------------------------------


4. Criação da entidade:

--------------------------------------------------------
Entity player = scene.CreateEntity("Player");
--------------------------------------------------------
- Ou
--------------------------------------------------------
auto player = scene.CreateEntity("Player");
--------------------------------------------------------    


5. Adicionar componentes:

--------------------------------------------------------
player.Add<Transform>();
--------------------------------------------------------
- Depois
--------------------------------------------------------
player.Add<MeshRenderer>();
--------------------------------------------------------
- Depois
--------------------------------------------------------
player.Add<Rigidbody>();
--------------------------------------------------------  
- Depois
--------------------------------------------------------
player.Add<BoxCollider>();
--------------------------------------------------------


6. Obtendo componentes:

--------------------------------------------------------
auto& transform = player.Get<Transform>();
--------------------------------------------------------
- Ou
--------------------------------------------------------
player.Get<Rigidbody>();
--------------------------------------------------------    


7. Removendo componentes:

--------------------------------------------------------
player.Remove<Rigidbody>();
--------------------------------------------------------


8. Recursos

--------------------------------------------------------
auto knight = Resources::Load<Model>("Knight.fbx");
--------------------------------------------------------
- Ou
--------------------------------------------------------
auto shader = Resources::Load<Shader>("Default.shader");
--------------------------------------------------------    

9. Criação da câmera

--------------------------------------------------------
auto camera = scene.CreateEntity("Main Camera");
camera.Add<Camera>();
--------------------------------------------------------


10. Scripts

--------------------------------------------------------
class PlayerController : public Script
{
public:
    void OnCreate() override;
    void OnUpdate(float dt) override;
    void OnDestroy() override;
};
--------------------------------------------------------
- Ou
--------------------------------------------------------
player.Add<PlayerController>();
--------------------------------------------------------   


11. Eventos

--------------------------------------------------------
EventBus::Subscribe<KeyPressedEvent>(...);

EventBus::Publish(PlayerDiedEvent());
--------------------------------------------------------
- Ou, se usar uma API mais orientada a instâncias:
--------------------------------------------------------
app.Events().Subscribe<KeyPressedEvent>(...);

app.Events().Publish(PlayerDiedEvent{});
--------------------------------------------------------   


12. Tempo

--------------------------------------------------------
Time::DeltaTime();
--------------------------------------------------------
- Ou
--------------------------------------------------------
Time::FPS();
--------------------------------------------------------    

13. Mudando a cena

--------------------------------------------------------
SceneManager::Load("Level02.scene");
--------------------------------------------------------
- Ou
--------------------------------------------------------
app.LoadScene("Level02");
--------------------------------------------------------

14. Executar a aplicação

--------------------------------------------------------
Application app("Primitive");

app.CreateScene("Main");

app.Run();
--------------------------------------------------------


15. Começo da api

--------------------------------------------------------
Application app("My Game");

Scene& scene = app.CreateScene("Game");

auto camera = scene.CreateEntity("Camera");
camera.Add<Camera>();

auto player = scene.CreateEntity("Player");

player.Add<Transform>();
player.Add<MeshRenderer>();
player.Add<Rigidbody>();
player.Add<PlayerController>();

auto model = Resources::Load<Model>("player.fbx");

player.Get<MeshRenderer>().SetModel(model);

app.Run();
--------------------------------------------------------