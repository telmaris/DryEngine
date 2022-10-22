cmake_minimum_required(VERSION 3.23)
project(DryEngine)

set(SDL2_LIBRARY "C:/SDL for VS/SDL2-devel-2.0.14-VC/SDL2-2.0.14/lib/x64/")

include_directories("C:/SDL for VS/SDL2-devel-2.0.14-VC/SDL2-2.0.14/include")

include_directories(inc)
add_subdirectory(src)