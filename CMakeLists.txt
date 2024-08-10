cmake_minimum_required(VERSION 3.29)
project(MyProject)

# Set Clang as the compiler
set(CMAKE_C_COMPILER "C:/Program Files/LLVM/bin/clang.exe")
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang++.exe")

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set optimization flags for Release builds
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

# Include FetchContent module for downloading dependencies
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

# Fetch entt
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.13.2
)
FetchContent_MakeAvailable(entt)

# Specify the source files
file(GLOB PROJECT_SOURCES "src/*.cpp" "src/Components/*.hpp" "src/Systems/*.hpp" "src/Systems/*.cpp")

# Your project's source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link raylib to your project
target_link_libraries(${PROJECT_NAME} raylib)

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${entt_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/src/Components
  ${CMAKE_SOURCE_DIR}/src/Systems
)

# Ensure raylib defines are set
if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
