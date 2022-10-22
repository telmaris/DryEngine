cmake_minimum_required(VERSION 3.23)
project(Lakefields)

set(SDL2_LIBRARY "C:/SDL for VS/SDL2-devel-2.0.14-VC/SDL2-2.0.14/lib/x64/")
include_directories("C:/SDL for VS/SDL2-devel-2.0.14-VC/SDL2-2.0.14/include")

set(DRYENGINE "C:/Users/Arek/Desktop/Projekty/DryEngineLib/build/src/Debug/")
include_directories("C:/Users/Arek/Desktop/Projekty/DryEngineLib/inc")

include_directories(inc)

add_library(sources "")

add_subdirectory(src)

add_executable(lakefields 
               main.cpp)

target_link_libraries(lakefields
                    sources
                    "${DRYENGINE}/DryEngine.lib"
                    "${SDL2_LIBRARY}/SDL2.lib" 
                    "${SDL2_LIBRARY}/SDL2main.lib"
                    "${SDL2_LIBRARY}/SDL2_image.lib"
                    "${SDL2_LIBRARY}/SDL2_mixer.lib")