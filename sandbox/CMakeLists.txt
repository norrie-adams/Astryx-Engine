file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable(AstryxSandbox ${SANDBOX_SOURCES})

target_link_libraries(AstryxSandbox PRIVATE Engine)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

target_compile_definitions(AstryxSandbox PRIVATE 
    SANDBOX_ASSET_DIR="${CMAKE_CURRENT_BINARY_DIR}/assets/"
)
