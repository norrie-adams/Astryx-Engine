file(GLOB_RECURSE SANDBOX_SOURCES "*.cpp")

add_executable(AstryxSandbox ${SANDBOX_SOURCES})

target_link_libraries(AstryxSandbox PRIVATE Engine)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
