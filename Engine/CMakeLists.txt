add_library(PrimitiveEngine STATIC
    Core/src/Engine.cpp
    Core/src/Application.cpp
    Core/src/Time.cpp
    Core/src/Logger.cpp
    Core/src/FileSystem.cpp
    Core/src/EventBus.cpp
    Core/src/Events/WindowEvents.cpp
    Core/src/Configuration.cpp
    Core/src/LayerStack.cpp

    Platform/src/Platform.cpp
    Platform/src/Window.cpp
    Platform/src/Input.cpp
    Platform/src/SDL/SDLInput.cpp

    Resources/src/ResourceManager.cpp
    Resources/src/ModelLoader.cpp
    Resources/src/TextureLoader.cpp
    
    Renderer/src/Renderer.cpp
    Renderer/src/VertexBufferLayout.cpp
    Renderer/src/Camera.cpp
    Renderer/src/Mesh.cpp
    Renderer/src/Model.cpp
    Renderer/src/Material.cpp
    Renderer/src/OpenGL/OpenGLTextureLoader.cpp
    Renderer/src/OpenGL/OpenGLTexture.cpp
    Renderer/src/OpenGL/OpenGLRenderer.cpp
    Renderer/src/OpenGL/OpenGLShader.cpp
    Renderer/src/OpenGL/OpenGLShaderLoader.cpp
    Renderer/src/OpenGL/OpenGLVertexBuffer.cpp
    Renderer/src/OpenGL/OpenGLVertexArray.cpp
    Renderer/src/OpenGL/OpenGLRendererFactory.cpp
    Renderer/src/OpenGL/OpenGLIndexBuffer.cpp
    Renderer/src/OpenGL/OpenGLFrameBuffer.cpp

    Scene/src/Scene.cpp
    Scene/src/Entity.cpp
    Scene/src/EntityManager.cpp
    Scene/src/Transform.cpp
    Scene/src/SceneSerializer.cpp

    Physics/src/PhysicsWorld.cpp
    Physics/src/Bounds.cpp
    Physics/src/NarrowPhase.cpp
    Physics/src/BroadPhase.cpp
    Physics/src/AABB.cpp
    Physics/src/FixedTimeStep.cpp

    Assets/src/AssetHandleGenerator.cpp
    Assets/src/AssetRegistry.cpp
    Assets/src/AssetManager.cpp
    Assets/src/AssetDiscovery.cpp
    Assets/src/Importer/AssetImporterRegistry.cpp
    Assets/src/Importer/ModelAssetImporter.cpp
    Assets/src/Importer/TextureAssetImporter.cpp
    Assets/src/Importer/ShaderAssetImporter.cpp
    Assets/src/Importer/SceneAssetImporter.cpp
    
    Project/src/Project.cpp
)

target_include_directories(PrimitiveEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Physics/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Project/include
        ${stb_SOURCE_DIR}
)

target_compile_features(
    PrimitiveEngine
    PUBLIC
        cxx_std_23
)

target_compile_options(PrimitiveEngine PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/permissive->
)

target_link_libraries(
    PrimitiveEngine
    PUBLIC
        SDL3::SDL3   
        glad_gl_core_46
        glm::glm
        assimp::assimp
        nlohmann_json::nlohmann_json
)