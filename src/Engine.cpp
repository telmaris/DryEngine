#include "../inc/DryEngine.hpp"

namespace dryengine
{
    const char *tag = "DryEngine";

    namespace sdl
    {
        const char *tag = "SDL";

        SDL::SDL(bool& error)
        {
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
            {
                LOGE(tag, SDL_GetError());
                error = true;
                return;
            }

            if (IMG_Init(IMG_INIT_PNG) == 0)
            {
                LOGE(tag, SDL_GetError());
                error = true;
                return;
            }

            if (Mix_Init(MIX_INIT_MP3) < 0)
            {
                LOGE(tag, SDL_GetError());
                error = true;
                return;
            }

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
            {
                LOGE(tag, SDL_GetError());
                error = true;
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
                error = true;
                return;
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

            if (!renderer)
            {
                LOGE(tag, SDL_GetError());
                error = true;
                return;
            }

            error = false;
            LOGI(tag, "Initialized successfully!");
        }
    
        SDL::~SDL()
        {
            SDL_DestroyRenderer(renderer);
		    SDL_DestroyWindow(window);

		    Mix_CloseAudio();
            IMG_Quit();
		    SDL_Quit();
        }
    }

    EngineStatus::EngineStatus(const bool& error)
    {
        gameRunning = !(error);
        fpsCap = 60;
        delay = 1000.0 / fpsCap;
    }

    DryEngine::DryEngine()
    {
        bool error = false;
        sdlWrapper = std::make_unique<sdl::SDL>(error);
        status = std::make_unique<EngineStatus>(error);

        currentScene = std::make_shared<scene::Scene>(sdlWrapper->renderer, MAX_SCENES);    // engine creates a default scene. It is deleted after changing
    }

    DryEngine::~DryEngine()
    {
        
    }

    std::shared_ptr<scene::Scene> DryEngine::CreateScene(SceneID id)
    {
        if(scenes.find(id) != scenes.end())
        {
            LOGE(tag, "Scene creation error. Scene with this ID exists. Returning nullptr.");
            //return std::shared_ptr<scene::Scene>(nullptr);
            return nullptr;
        }

        auto scene = std::make_shared<scene::Scene>(sdlWrapper->renderer, id);
        scenes.insert({id, scene});
        return scene;
    }

    void DryEngine::ChangeScene(SceneID id)
    {
        currentScene = scenes[id];
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

            SDL_Delay(static_cast<Uint32>(dt*1000));
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

    SDL_Renderer* DryEngine::MainRenderer()
    {
        return sdlWrapper->renderer;
    }
}