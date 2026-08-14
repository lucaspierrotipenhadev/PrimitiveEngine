add_library(PrimitiveEngine STATIC
    Core/src/Engine.cpp
    Core/src/Application.cpp
    Core/src/Time.cpp
    Core/src/Logger.cpp
    Core/src/FileSystem.cpp
    Core/src/EventBus.cpp
    Core/src/Events/WindowEvents.cpp
    Core/src/Configuration.cpp

    Platform/src/Platform.cpp
    Platform/src/Window.cpp
    Platform/src/Input.cpp
    Platform/src/SDL/SDLInput.cpp

    Resources/src/ResourceManager.cpp
    
    Renderer/src/Renderer.cpp
    Renderer/src/VertexBufferLayout.cpp
    Renderer/src/OpenGL/OpenGLRenderer.cpp
    Renderer/src/OpenGL/OpenGLShader.cpp
    Renderer/src/OpenGL/OpenGLShaderLoader.cpp
    Renderer/src/OpenGL/OpenGLVertexBuffer.cpp
    Renderer/src/OpenGL/OpenGLVertexArray.cpp
    Renderer/src/OpenGL/OpenGLRendererFactory.cpp
)

target_include_directories(PrimitiveEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/include
)

target_compile_features(
    PrimitiveEngine
    PUBLIC
        cxx_std_23
)

target_link_libraries(
    PrimitiveEngine
    PUBLIC
        SDL3::SDL3   
        glad_gl_core_46
)