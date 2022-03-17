cmake_minimum_required (VERSION 3.16.3)
project(Particles)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")
# Commentaire
add_executable(benchmark particule.cpp)
add_executable(main main.cpp)