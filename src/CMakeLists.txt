cmake_minimum_required(VERSION 3.23)

target_sources(sources
               PRIVATE
               Utils.cpp
               Scene.cpp
               Engine.cpp
               ComponentManager.cpp
               EntityManager.cpp
               SystemManager.cpp
               EventManager.cpp
               RenderManager.cpp
               Maths.cpp
               Systems.cpp)