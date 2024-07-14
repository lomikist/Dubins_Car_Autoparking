cmake_minimum_required(VERSION 3.10)
project(ImGuiExample)

set(CMAKE_CXX_STANDARD 11)

# Set policy CMP0072 to prefer GLVND
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include ImGui files
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)

file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
)

add_executable(app src/main.cpp ${IMGUI_SOURCES})

include_directories(imgui)

target_link_libraries(app PRIVATE sfml-system sfml-window sfml-graphics OpenGL::GL)
