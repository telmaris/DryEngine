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
            SDL(bool* error);

            SDL_Window *window;
            SDL_Renderer *renderer;
            SDL_Texture *mainTexture;
        };
    }

    struct EngineStatus
    {
        EngineStatus(bool* error);

        bool gameRunning;
        int fpsCap;
        double delay;
    };

    class DryEngine
    {
    public:
        DryEngine();

        void loop();

    private:
        std::unique_ptr<EngineStatus> status;
        std::unique_ptr<sdl::SDL> sdlWrapper;
        std::unique_ptr<systemmgr::SystemManager> systemManager;
        std::unique_ptr<entitymgr::EntityManager> entityManager;
        std::unique_ptr<componentmgr::ComponentManager> componentManager;
    };
}