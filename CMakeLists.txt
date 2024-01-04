project(pathtracer)
cmake_minimum_required(VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(PNG REQUIRED)


file(GLOB_RECURSE sources "src/*.cpp" "src/*.hpp")
include_directories("src/lib" ${EIGEN3_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${PNG_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
add_library(tiny_obj_loader STATIC "src/lib/tiny_obj_loader.cc" "src/lib/tiny_obj_loader.h")
link_directories("/opt/homebrew/Cellar/glew/2.2.0_1/lib")

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Ofast -Wall -Weffc++ -Wuninitialized")
# Update linker flags for macOS
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OpenGL")

add_executable(pathtracer ${sources})
target_link_libraries(pathtracer tiny_obj_loader Eigen3::Eigen glfw ${OPENGL_LIBRARIES} ${PNG_LIBRARY} ${GLFW_LIBRARIES} /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.dylib)
