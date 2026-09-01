add_executable(
    PrimitiveTests
    src/main.cpp
)

target_link_libraries(
    PrimitiveTests
    PRIVATE
        PrimitiveEngine
)