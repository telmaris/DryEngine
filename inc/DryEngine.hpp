#pragma once

#include "Utils.hpp"
#include "Scene.hpp"

namespace dryengine
{
    namespace sdl
    {
        struct SDL
        {
            SDL(bool& error);
            ~SDL();

            SDL_Window *window;
            SDL_Renderer *renderer;
            SDL_Texture *mainTexture;
            SDL_Texture *lightPoints;
        };
    }

    struct EngineStatus
    {
        EngineStatus(const bool& error);

        bool gameRunning;
        int fpsCap;
        double delay;
    };

    class DryEngine
    {
    public:
        DryEngine();
        ~DryEngine();

        void loop();

        std::shared_ptr<scene::Scene> CreateScene(SceneID id);
        void ChangeScene(SceneID id);

    private:
        void Events();
        void Render();
        void Update(double dt);

        std::unique_ptr<EngineStatus> status;
        std::unique_ptr<sdl::SDL> sdlWrapper;
        std::shared_ptr<scene::Scene> currentScene;

        std::map<SceneID, std::shared_ptr<scene::Scene>> scenes;
    };
}