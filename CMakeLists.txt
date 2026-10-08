cmake_minimum_required(VERSION 3.24)
project(LSM_Tree_KV_Store DESCRIPTION "An LSM-tree storage engine, built using Cpp" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
  $<$<CONFIG:Debug>:-fsanitize=address,undefined>
  $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
  -Wall
  -Wextra
)
add_link_options($<$<CONFIG:Debug>:-fsanitize=address,undefined>)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/988ea2c1798de7779f656df2281dd36d6039a17a.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(Engine STATIC src/engine.cpp)
target_include_directories(Engine PUBLIC include)
add_executable(CLIExec apps/main.cpp)
target_link_libraries(CLIExec PRIVATE Engine)
add_executable(TestEngine tests/engine_test.cpp)
target_link_libraries(TestEngine PRIVATE Engine GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(TestEngine)