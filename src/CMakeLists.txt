cmake_minimum_required(VERSION 3.23)

add_subdirectory(levels)

target_sources(sources
               PRIVATE
               Lakefields.cpp
               MainMenu.cpp
               levels/DemoArea1.cpp)