#pragma once

#include "../../Level.hpp"

using namespace dryengine;

namespace lakefields
{
    class DemoArea2 : public ILevel
    {
    public:
        DemoArea() = default;




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
            Entity e_hero;
        };

        Terrain terrain;
        Objects objects;
        Hero hero;
    };
}