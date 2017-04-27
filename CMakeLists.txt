project(pathtracer)
cmake_minimum_required(VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE sources "src/*.cpp" "src/*.hpp")
include_directories("src/lib")
add_library(tiny_obj_loader STATIC "src/lib/tiny_obj_loader.cc" "src/lib/tiny_obj_loader.h")

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Ofast -Wall -Weffc++ -Wuninitialized")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lGLEW -lGLU -lSOIL -lX11 -lXi -lXrandr -lXxf86vm -lglfw -lpng -lprofiler -lpthread")

add_executable(pathtracer ${sources})
target_link_libraries(pathtracer tiny_obj_loader)
