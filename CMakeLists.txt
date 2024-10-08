cmake_minimum_required(VERSION 3.29)
project(MyProject)

# Set the generator to Ninja
set(CMAKE_GENERATOR "Ninja")

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Fetch nlohmann/json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

# Specify the source files
file(GLOB PROJECT_SOURCES 
  "src/*.cpp" 
  "src/Components/*.hpp" 
  "src/Systems/*.hpp" 
  "src/Systems/*.cpp"
)

# Your project's source files
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link raylib to your project
target_link_libraries(${PROJECT_NAME} raylib)

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE 
  ${entt_SOURCE_DIR}/src
  ${json_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/src/Components
  ${CMAKE_SOURCE_DIR}/src/Systems
)

# Add compiler flags to disable exceptions
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:GNU>:-fno-exceptions>
  $<$<CXX_COMPILER_ID:Clang>:-fno-exceptions>
  $<$<CXX_COMPILER_ID:MSVC>:/EHs->
)

# Custom target to build and run the project
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target ${PROJECT_NAME} -- -j 8
    COMMAND ${CMAKE_COMMAND} -E echo "Running executable..."
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    USES_TERMINAL
)
