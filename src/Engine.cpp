#include "../inc/Engine.hpp"

namespace dryengine
{
    namespace sdl
    {
        const char* tag = "SDL";

        SDL::SDL()
        {
            if(SDL_Init(SDL_INIT_EVERYTHING))
            {
                LOGE(tag, SDL_GetError());
            }

            LOGI(tag, "Working!");

        }
    }

    DryEngine::DryEngine()
    {
        systemManager = std::make_unique<systemmgr::SystemManager>();
        entityManager = std::make_unique<entitymgr::EntityManager>();
        componentManager = std::make_unique<componentmgr::ComponentManager>();
    }
}