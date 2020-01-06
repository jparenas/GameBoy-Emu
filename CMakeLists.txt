project (GameBoy)

cmake_minimum_required(VERSION 3.15.3)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

include_directories(include 
  ${SDL2_INCLUDE_DIRS} 
  ${OPENGL_INCLUDE_DIRS}  
  ${GLUT_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")
add_executable(GameBoy ${SOURCES})
target_compile_options(GameBoy PRIVATE -std=c++2a)
target_link_libraries(GameBoy ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})
