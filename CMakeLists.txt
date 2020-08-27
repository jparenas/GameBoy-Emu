cmake_minimum_required(VERSION 3.16.0)

project(GameBoy VERSION 0.0.1)

set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/imgui ${CMAKE_SOURCE_DIR}/imgui/examples ${CMAKE_SOURCE_DIR}/imgui_club)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

file(
	GLOB IMGUI_SOURCES
		"imgui/imgui.cpp"
		"imgui/imgui_draw.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/*.h"
    "imgui/examples/imgui_impl_sdl.cpp"
    "imgui/examples/imgui_impl_sdl.h"
    "imgui/examples/imgui_impl_opengl3.cpp"
    "imgui/examples/imgui_impl_opengl3.h"
)

include_directories(include 
  ${SDL2_INCLUDE_DIRS} 
  ${OPENGL_INCLUDE_DIRS}  
  ${GLEW_INCLUDE_DIRS}
  ${IMGUI_INCLUDE_DIR})

message(STATUS "GLEW Directory" ${GLEW_LIBRARIES})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
add_library(imgui STATIC ${IMGUI_SOURCES} ${GLEW_INCLUDE_DIRS})
target_link_libraries(imgui GLEW::GLEW ${OPENGL_LIBRARIES})

add_subdirectory(CLI11)

file(GLOB SOURCES "src/*.cpp")
add_executable(GameBoy ${SOURCES})
target_compile_options(GameBoy PRIVATE -std=c++2a -g)
target_link_libraries(GameBoy imgui CLI11::CLI11 GLEW::GLEW ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
