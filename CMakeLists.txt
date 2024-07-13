cmake_minimum_required(VERSION 3.20)

project(Car_Autoparking)
set(EXECUTABLE "app")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

include_directories(include)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")

add_executable(${EXECUTABLE} ${CPP_SOURCES})

target_link_libraries(${EXECUTABLE} PRIVATE sfml-system sfml-window sfml-graphics)

target_compile_options(${EXECUTABLE} PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-g3>
)

set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../release
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../debug
)
