cmake_minimum_required(VERSION 3.25)

project(
    PrimitiveEngine
    VERSION 0.1.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# --- SDL3 ---
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3)

# --- GLAD 2 ---
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(glad)

# Adiciona o diretório cmake do GLAD ao CMAKE_MODULE_PATH
list(APPEND CMAKE_MODULE_PATH "${glad_SOURCE_DIR}/cmake")

# Gera o código C do OpenGL 4.6 Core dinamicamente
glad_add_library(
    glad_gl_core_46
    STATIC
    REPRODUCIBLE
    LOCATION "${CMAKE_BINARY_DIR}/glad"
    API gl:core=4.6
)

# --- GLM ---

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glm)

add_subdirectory(Engine)
add_subdirectory(Sandbox)