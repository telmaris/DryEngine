#pragma once

#include "Utils.hpp"
#include "SystemManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"

namespace dryengine
{
    namespace sdl
    {
        struct SDL
        {
            SDL();

            SDL_Window* window;
            SDL_Renderer* renderer;
            SDL_Texture* mainTexture;
        };
    }

    class DryEngine
    {
        public:
            DryEngine();

        private:
            sdl::SDL sdlWrapper;

            std::unique_ptr<systemmgr::SystemManager> systemManager;
            std::unique_ptr<entitymgr::EntityManager> entityManager;
            std::unique_ptr<componentmgr::ComponentManager> componentManager;
    };
}