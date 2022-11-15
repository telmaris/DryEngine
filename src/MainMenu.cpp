#include "MainMenu.hpp"

using namespace dryengine;

namespace lakefields
{   
    

    

    // ===== SCRIPTS =====

    // Main Menu Quit button script (closing the game)
    void script_menuQuitButton(double dt, Entity e)
    {
        SDL_Rect box = {840, 600, 240, 80};
        if(MenuScene()->EventManager()->MouseClick(1, box)) rEngine()->StopEngine();
    }

    void script_menuNewGameButton(double dt, Entity e)
    {
        SDL_Rect box = {840, 300, 240, 80};

        if(MenuScene()->EventManager()->MouseClick(1, box))
        {
            //currentSubmenu = SUBMENU::MAIN;
        }
    }

    // ===================

    std::shared_ptr<scene::Scene> MainMenu::CreateMainMenu()
    {
        scene = rEngine()->CreateScene(0);
        rEngine()->ChangeScene(0);

        return scene;
    }

    void MainMenu::InitEntities()
    {
        currentSubmenu = SUBMENU::MAIN;

        //create menu main camera
        mainsub.e_menuCamera = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuCamera, core::Transform{0,0});
        scene->AddComponent(mainsub.e_menuCamera, core::Camera{math::Vector2{WINDOW_SIZE_X, WINDOW_SIZE_Y}});

        //create background entity
        mainsub.e_menuBackground = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuBackground, core::Transform{0,0});
        scene->AddComponent(mainsub.e_menuBackground, core::Graphics{});
        scene->RenderManager()->LoadGraphics(mainsub.e_menuBackground, "assets/mainmenu/sprites/bg.png", 0);

        //create new game button entity
        mainsub.e_menuNewGameButton = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuNewGameButton, core::Transform{840,300});
        scene->AddComponent(mainsub.e_menuNewGameButton, core::Graphics{});
        //scene->AddComponent(mainsub.e_menuNewGameButton, core::Script{});
        scene->RenderManager()->LoadGraphics(mainsub.e_menuNewGameButton, "assets/mainmenu/sprites/new_game.png", 0);

        //create load game button entity
        mainsub.e_menuLoadGameButton = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuLoadGameButton, core::Transform{840,400});
        scene->AddComponent(mainsub.e_menuLoadGameButton, core::Graphics{});
        //scene->AddComponent(mainsub.e_menuLoadGameButton, core::Script{});
        scene->RenderManager()->LoadGraphics(mainsub.e_menuLoadGameButton, "assets/mainmenu/sprites/load_game.png", 0);

        //create options button entity
        mainsub.e_menuOptionsButton = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuOptionsButton, core::Transform{840,500});
        scene->AddComponent(mainsub.e_menuOptionsButton, core::Graphics{});
        //scene->AddComponent(mainsub.e_menuOptionsButton, core::Script{});
        scene->RenderManager()->LoadGraphics(mainsub.e_menuOptionsButton, "assets/mainmenu/sprites/options.png", 0);

        //create quit button entity
        mainsub.e_menuQuitButton = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuQuitButton, core::Transform{840,600});
        scene->AddComponent(mainsub.e_menuQuitButton, core::Graphics{});
        scene->AddComponent(mainsub.e_menuQuitButton, core::Script{script_menuQuitButton});
        scene->RenderManager()->LoadGraphics(mainsub.e_menuQuitButton, "assets/mainmenu/sprites/quit.png", 0);

        //create logo entity
        mainsub.e_menuLogo = scene->CreateEntity();
        scene->AddComponent(mainsub.e_menuLogo, core::Transform{720,100});
        scene->AddComponent(mainsub.e_menuLogo, core::Graphics{});
        scene->RenderManager()->LoadGraphics(mainsub.e_menuLogo, "assets/mainmenu/sprites/logo.png", 0);
    }

    MainMenu::~MainMenu()
    {

    }

    
}