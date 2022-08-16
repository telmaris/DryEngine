#pragma once

#include "Utils.hpp"
#include "Scene.hpp"

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
        std::shared_ptr<scene::Scene> currentScene;
    };
}