cmake_minimum_required(VERSION 3.16.0)

project(GameBoy VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)

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
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLEW)
add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_SOURCES})
target_link_libraries(imgui ${OPENGL_LIBRARIES})


include_directories(include 
  ${SDL2_INCLUDE_DIRS} 
  ${OPENGL_INCLUDE_DIRS}  
  ${GLEW_INCLUDE_DIRS}
  ${IMGUI_INCLUDE_DIR})

add_subdirectory(CLI11)

file(GLOB SOURCES "src/*.cpp")
add_executable(GameBoy ${SOURCES})
target_compile_options(GameBoy PRIVATE -std=c++2a -g)
target_link_libraries(GameBoy ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} CLI11::CLI11 imgui)
