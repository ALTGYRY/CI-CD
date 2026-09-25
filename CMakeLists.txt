cmake_minimum_required(VERSION 3.14)

set(PATCH_VERSION "1" CACHE STRING "Patch version")

project(
    helloworld
    VERSION "0.0.${PATCH_VERSION}"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Скачиваем и подключаем GoogleTest
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
)

# Нужна для корректной сборки в Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/version.h"
    @ONLY
)

add_library(helloworld lib.cpp)

target_include_directories(
    helloworld
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
)

add_executable(helloworld_cli main.cpp)

target_link_libraries(
    helloworld_cli
    PRIVATE helloworld
)

# Тестовая программа
add_executable(test_version test_version.cpp)

target_link_libraries(
    test_version
    PRIVATE
        helloworld
        GTest::gtest_main
)

if(MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version PRIVATE /W4)
else()
    target_compile_options(
        helloworld_cli PRIVATE
        -Wall -Wextra -Wpedantic -Werror
    )
    target_compile_options(
        helloworld PRIVATE
        -Wall -Wextra -Wpedantic -Werror
    )
    target_compile_options(
        test_version PRIVATE
        -Wall -Wextra -Wpedantic -Werror
    )
endif()

# Подключение тестов к CTest
enable_testing()
include(GoogleTest)
gtest_discover_tests(test_version)

install(
    TARGETS helloworld_cli
    RUNTIME DESTINATION bin
)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT "example@example.com")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(
    CPACK_PACKAGE_FILE_NAME
    "${PROJECT_NAME}-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}"
)
include(CPack)