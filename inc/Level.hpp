#pragma once

#include "Game.hpp"

using namespace dryengine;

namespace lakefields
{
    class ILevel : public IGameScene
    {
    public:
        virtual ~ILevel() = default;

        uint32_t levelID;
        Geometry defaultPositionAndSizeVector;
    };
}