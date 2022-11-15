#pragma once

#include "Game.hpp"

using namespace dryengine;

namespace lakefields
{
    enum class SUBMENU : uint8_t
    {
        MAIN,
        OPTIONS,
        LOADGAME
    };

    class MainMenu : public IGameScene
    {
    public:
        MainMenu() = default;
        MainMenu(MainMenu &) = delete;
        MainMenu(MainMenu &&) = delete;
        ~MainMenu();

        std::shared_ptr<scene::Scene> CreateMainMenu();
        void InitEntities();

    private:
        struct MainSubmenu
        {
            Entity e_menuCamera;
            Entity e_menuBackground;
            Entity e_menuNewGameButton;
            Entity e_menuLoadGameButton;
            Entity e_menuOptionsButton;
            Entity e_menuQuitButton;
            Entity e_menuVersionLabel;
            Entity e_menuScriptController;
            Entity e_menuLogo;

            bool active = true;
        };

        struct OptionsSubmenu
        {
            Entity e_menu_optionsBackButton;
            Entity e_menu_optionsMuteAudioBox;
            Entity e_menu_optionsSoundVolumeSlider;

            bool active = false;
        };

        struct LoadGameSubmenu
        {
            Entity e_menu_loadBackButton;
            // tbd;

            bool active = false;
        };

        MainSubmenu mainsub;
        OptionsSubmenu optionssub;
        LoadGameSubmenu loadsubmenu;

        std::shared_ptr<scene::Scene> menuScene;

        SUBMENU currentSubmenu;
    };

    void InitMainMenu();
    std::unique_ptr<MainMenu>& rMainMenu();

}