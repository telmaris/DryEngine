cmake_minimum_required(VERSION 3.23)

target_sources(sources
               PRIVATE
               Utils.cpp
               Maths.cpp
               Systems.cpp
               ComponentManager.cpp
               EntityManager.cpp
               SystemManager.cpp
               EventManager.cpp
               RenderManager.cpp
               Scene.cpp
               Engine.cpp)