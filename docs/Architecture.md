1. Visão Geral:

Primitive Engine será uma engine 2D/3D moderna desenvolvida em c++ 20 com foco em arquitetura modular, desempenho e simplicidade de uso.
Seu objetivo não é concorrer com engines consolidades, mas demonstrar engenharia de softwate aplicada à programação gráfica.

2. Objetivos:

Ter Engine 2/3D, ter um ECS própio, ter um editor, ter física, ter asset manager, ter scripts, ter uma API simples, e ser multiplataforma.

3. Não objetivos:

Não competir com grandess empresas, não suportar todas APIs gráficas inicialmente, e não implementar sistema de networking na primeira versão.

4. Filosofia:

O usuário nunca deverá ter de interagir diretamente com bibliotecas gráficas (SDL, OpenGL).
Toda funcionalidade deverá ser acessível através da API pública da engine.
***** Cada módulo deverá ter apenas uma responsabilidade *****


5. Arquitetura geral, (tudo separado):

- Alta coesão
- Baixo acoplamento
- Cada módulo conhece apenas os módulos imediatamente inferiores.
- Nunca existirão dependências circulares.
- A Engine nunca dependerá do Editor.
- O Editor dependerá da Engine.
- A Sandbox dependerá da Engine.
- Os jogos dependerão apenas da API pública.
- Todo recurso será gerenciado por RAII.
- Nenhum módulo poderá acessar OpenGL diretamente, exceto RenderAPI/OpenGL.

------------------------------------------------------------------------------------------------

    Editor
        │
        ▼
    Sandbox
        │
        ▼
    Engine
    ├── Core
    ├── ECS
    ├── Renderer
    ├── Physics
    ├── Audio
    ├── Resources
    └── Scene
            │
            ▼
            SDL3
            OpenGL

-------------------------------------------------------------------------------------------------------

5.1 Aplicação:

Application
↓
Engine
↓
Scene Manager
↓
Scene
↓
Systems
↓
Entities
↓
Components

5.2 Renderização:

Renderer
↓
Render API
↓
IRendererAPI
↓
OpenGL, DirectX, ou Vulcan

5.3 Física:

Physics
↓
Broad Phase
↓
Narrow Phase
↓
Collision Resolution

6. Organização dos módulos:
- Core
- Renderer
- Scene
- ECS
- Physics
- Animation
- Resources
- Audio
- Math
- Input
- Editor

7. Ciclo de vida

Initialize
↓
Load Assets
↓
Create Scene
↓
Start
↓
Game Loop
↓
Shutdown

8. Game Loop:

Poll Events
↓
Update Input
↓
Run Scripts
↓
Physics
↓
Animation
↓
Rendering
↓
Audio
↓
Swap Buffers

9. Convenções:

Namespaces, pastas, includes, tudo padronizado. (CodingGuidelines).

10. Road Map:
- Foundation : v0.1

Resultado esperado

✔ Engine inicializa
✔ SDL funcionando
✔ OpenGL funcionando
✔ Shader compila
✔ Tela limpa
✔ Input funcionando
✔ Game Loop funcional