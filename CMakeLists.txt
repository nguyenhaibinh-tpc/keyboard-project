cmake_minimum_required(VERSION 3.17)
project(keyboard_project)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(keyboard_project main.cpp Manager.cpp Manager.h TextureLoader.cpp TextureLoader.h Button.cpp Button.h AnimatedObject.cpp AnimatedObject.h)
target_link_libraries(keyboard_project ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)
