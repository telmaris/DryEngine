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
        currentScene = std::make_shared<scene::Scene>();    // engine creates a default scene. It is deleted after changing
    }

    void DryEngine::loop()
    {
        LOGI(tag, "Entering mainloop...");

        std::cout << "currentScene counter: " << currentScene.use_count() << std::endl;
        std::cout << "currentScene address: " << currentScene.get() << std::endl;

        double dt = 0.01;

        while (status->gameRunning)
        {
            Events();
            Update(dt);
            Render();

            SDL_Delay(dt*1000);
        }

        LOGI(tag, "Leaving mainloop...");
    }

    void DryEngine::Render()
    {
        currentScene->Render();
    }

    void DryEngine::Update(double dt)
    {
        currentScene->Update(dt);
    }

    void DryEngine::Events()
    {
        SDL_PumpEvents();
        currentScene->ProcessEvents(&status->gameRunning);
    }
}