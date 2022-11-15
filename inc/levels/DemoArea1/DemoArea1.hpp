#pragma once

#include "../../Level.hpp"

using namespace dryengine;

namespace lakefields
{
    class DemoArea1 : public ILevel
    {
    public:
        DemoArea1() = default;

        std::shared_ptr<scene::Scene> CreateDemoArea1();
        void InitEntities();

    private:

        void LoadTextures();

        struct Terrain
        {
            Entity e_land;
        };

        struct Objects
        {
            Entity e_tree1;
            Entity e_tree2;
            Entity e_tree3;
        };

        struct Hero
        {
            Entity e_camera;
            Entity e_hero;
        };

        Terrain terrain;
        Objects objects;
        Hero hero;
    };
}