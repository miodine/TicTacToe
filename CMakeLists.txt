cmake_minimum_required(VERSION 3.0)
project(Test)


set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.c)
if (NOT TARGET raylib)
  find_package(raylib 2.5.0 REQUIRED)
endif()
target_link_libraries(${PROJECT_NAME} raylib)
