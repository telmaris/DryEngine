#include "levels/DemoArea1/DemoArea1.hpp"

using namespace dryengine;

namespace lakefields
{
    // ===== SCRIPTS =====

    // ===================

    std::shared_ptr<scene::Scene> DemoArea1::CreateDemoArea1()
    {
        scene = rEngine()->CreateScene(1);

        return scene;
    }

    void DemoArea1::InitEntities()
    {
        // Camera is attached to the hero
        hero.e_camera = scene->CreateEntity();
        scene->AddComponent(hero.e_camera, core::Transform{WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2});
        scene->AddComponent(hero.e_camera, core::Camera{math::Vector2{WINDOW_SIZE_X, WINDOW_SIZE_Y}});

        terrain.e_land = scene->CreateEntity();
        scene->AddComponent(terrain.e_land, core::Transform{0,0});
        scene->AddComponent(terrain.e_land, core::Graphics{});

        objects.e_tree1 = scene->CreateEntity();
        scene->AddComponent(objects.e_tree1, core::Transform{0,0});
        scene->AddComponent(objects.e_tree1, core::Graphics{});

        objects.e_tree2 = scene->CreateEntity();
        scene->AddComponent(objects.e_tree2, core::Transform{0,0});
        scene->AddComponent(objects.e_tree2, core::Graphics{});

        objects.e_tree3 = scene->CreateEntity();
        scene->AddComponent(objects.e_tree3, core::Transform{0,0});
        scene->AddComponent(objects.e_tree3, core::Graphics{});

        hero.e_hero = scene->CreateEntity();
        scene->AddComponent(hero.e_hero, core::Transform{0,0});
        scene->AddComponent(hero.e_hero, core::Graphics{});

        LoadTextures();
    }

    void DemoArea1::LoadTextures()
    {

    }
}