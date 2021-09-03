cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
target_include_directories(SnakeGame PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_include_directories(SnakeGame PRIVATE include ${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})
