find_package(GTest CONFIG REQUIRED)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.cpp")
add_executable(ENGINE_TESTS ${TEST_SOURCES})

target_link_libraries(ENGINE_TESTS PRIVATE 
    Engine
    GTest::gtest 
    GTest::gtest_main
)

# Compatibilaty with older versions 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(GoogleTest)
gtest_discover_tests(ENGINE_TESTS)