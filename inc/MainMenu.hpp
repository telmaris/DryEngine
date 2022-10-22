#pragma once

#include "Game.hpp"

using namespace dryengine;

namespace lakefields
{
    std::shared_ptr<scene::Scene> CreateMainMenu(const std::unique_ptr<DryEngine>& engine);
}