#include "MainMenu.hpp"

using namespace dryengine;

namespace lakefields
{
    std::shared_ptr<scene::Scene> CreateMainMenu(const std::unique_ptr<DryEngine>& engine)
    {
        auto menuScene = engine->CreateScene();
        engine->ChangeScene(menuScene);

        //create menu main camera
        auto menuCamera = menuScene->CreateEntity();
        menuScene->AddComponent(menuCamera, core::Transform{0,0});

        return menuScene;
    }
}