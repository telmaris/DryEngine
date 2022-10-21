cmake_minimum_required(VERSION 3.23)
project(DryEngine)

set(SDL2_LIBRARY "C:/SDL for VS/SDL2-devel-2.0.14-VC/SDL2-2.0.14/lib/x64/")

include_directories("C:/SDL for VS/SDL2-devel-2.0.14-VC/SDL2-2.0.14/include")

include_directories(inc)
include_directories(tests)

add_library(sources "")

add_library(test_src "")

add_subdirectory(src)
add_subdirectory(tests)

add_executable(dry 
               main.cpp)

target_link_libraries(dry
                    sources
                    test_src
                    "${SDL2_LIBRARY}/SDL2.lib" 
                    "${SDL2_LIBRARY}/SDL2main.lib"
                    "${SDL2_LIBRARY}/SDL2_image.lib"
                    "${SDL2_LIBRARY}/SDL2_mixer.lib")