add_executable(PrimitiveSandbox
    src/main.cpp
)

target_link_libraries(
    PrimitiveSandbox
    PRIVATE
        PrimitiveEngine
)