add_library(PrimitiveEngine STATIC
    Core/src/Engine.cpp
    Core/src/Application.cpp
    Core/src/Time.cpp
)

target_include_directories(PrimitiveEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
)

target_compile_features(
    PrimitiveEngine
    PUBLIC
        cxx_std_20
)