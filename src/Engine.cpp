#include "../inc/Engine.hpp"

namespace dryengine
{
    const char *tag = "DryEngine";

    namespace sdl
    {
        const char *tag = "SDL";

        SDL::SDL(bool *error)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
            {
                LOGE(tag, SDL_GetError());
                *error = true;
                return;
            }

            if (IMG_Init(IMG_INIT_PNG) == 0)
            {
                LOGE(tag, SDL_GetError());
                *error = true;
                return;
            }

            if (Mix_Init(MIX_INIT_MP3) < 0)
            {
                LOGE(tag, SDL_GetError());
                *error = true;
                return;
            }

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
            {
                LOGE(tag, SDL_GetError());
                *error = true;
                return;
            }

            window = SDL_CreateWindow("DryEngine",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      WINDOW_SIZE_X, WINDOW_SIZE_Y,
                                      0);

            if (!window)
            {
                LOGE(tag, SDL_GetError());
                *error = true;
                return;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (!renderer)
            {
                LOGE(tag, SDL_GetError());
                *error = true;
                return;
            }

            *error = false;
            LOGI(tag, "Initialized successfully!");
        }
    }

    EngineStatus::EngineStatus(bool *error)
    {
        gameRunning = !(*error);
        fpsCap = 60;
        delay = 1000.0 / fpsCap;
    }

    DryEngine::DryEngine()
    {
        bool error = false;
        sdlWrapper = std::make_unique<sdl::SDL>(&error);
        status = std::make_unique<EngineStatus>(&error);
    }

    void DryEngine::loop()
    {
        LOGI(tag, "Entering mainloop...");

        SDL_PumpEvents();

		SDL_Event e = SDL_Event{};

        while (status->gameRunning)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    status->gameRunning = false;
                }
            }
        }
    }
}