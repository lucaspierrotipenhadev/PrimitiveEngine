cmake_minimum_required(VERSION 3.25)

project(
    PrimitiveEngine
    VERSION 0.1.0
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

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

list(APPEND CMAKE_MODULE_PATH "${glad_SOURCE_DIR}/cmake")

glad_add_library(
    glad_gl_core_46
    STATIC
    REPRODUCIBLE
    LOCATION "${CMAKE_BINARY_DIR}/glad"
    API gl:core=4.6
)

# --- GLM ---
# Garante que o GLM não tente compilar uma DLL/LIB própria
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

# --- Assimp ---
# Configurações do Assimp e ZLIB embutido
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)          # Força o build do zlib interno
set(ASSIMP_BUILD_ZLIB_STATIC ON CACHE BOOL "" FORCE)   # Garante zlib estático
set(ASSIMP_BUILD_ALL_IMPORTERS_OFF ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    assimp
    URL https://github.com/assimp/assimp/archive/refs/tags/v5.4.3.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(assimp)

# --- stb ---

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(stb)

# --- Dear ImGui ---

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui)

add_library(
    PrimitiveImGui STATIC

    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp

    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(
    PrimitiveImGui
    PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(
    PrimitiveImGui
    PRIVATE
        SDL3::SDL3
)

# --- ImGuizmo ---

FetchContent_Declare(
    imguizmo
    GIT_REPOSITORY https://github.com/CedricGuillemet/ImGuizmo.git
    GIT_TAG 1.10
    GIT_SHALLOW TRUE
)

FetchContent_GetProperties(imguizmo)

if(NOT imguizmo_POPULATED)
    FetchContent_Populate(imguizmo)
endif()

add_library(
    PrimitiveImGuizmo STATIC
    ${imguizmo_SOURCE_DIR}/src/ImGuizmo.cpp
)

target_include_directories(
    PrimitiveImGuizmo
    PUBLIC
        ${imguizmo_SOURCE_DIR}/src
)

target_link_libraries(
    PrimitiveImGuizmo
    PRIVATE
        PrimitiveImGui
)
#--------- ImgGuizo - fim

#------ nholman json

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_MakeAvailable(json)

#------ nholman json fim

#------ nfd

include(FetchContent)

FetchContent_Declare(
    nativefiledialog
    GIT_REPOSITORY https://github.com/btzy/nativefiledialog-extended.git
    GIT_TAG v1.3.0
)

FetchContent_MakeAvailable(nativefiledialog)

#------ nfd

add_subdirectory(Engine)
add_subdirectory(Editor)
add_subdirectory(Sandbox)