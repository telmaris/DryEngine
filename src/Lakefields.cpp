#include "../inc/Lakefields.hpp"

namespace lakefields
{
    
    auto e_lfEngine = std::make_unique<dryengine::DryEngine>(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    auto gs_mainMenu = std::make_unique<MainMenu>();
    auto s_mainmenu = gs_mainMenu->CreateMainMenu();

    auto gs_demoLevel1 = std::make_unique<DemoArea1>();

    // Lakefields engine reference. 
    std::unique_ptr<dryengine::DryEngine>& rEngine()
    {
        return e_lfEngine;
    }

    std::unique_ptr<MainMenu>& rMainMenu()
    {
        return gs_mainMenu;
    }

    std::shared_ptr<scene::Scene>& MenuScene()
    {
        return s_mainmenu;
    }

    void RunLakefields()
    {
        std::cout << "Lakefields launched";

        gs_mainMenu->InitEntities();
        e_lfEngine->loop();
    }
}

