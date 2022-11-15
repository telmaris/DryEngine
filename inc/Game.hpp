#pragma once

#include <DryEngine.hpp>
#include <memory>

#undef main
#undef WINDOW_SIZE_X
#undef WINDOW_SIZE_Y

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080


// game config

namespace lakefields
{
    // Engine unique_ptr reference getter.
    std::unique_ptr<dryengine::DryEngine>& rEngine();

    // === SCENE REFERENCES ===

    std::shared_ptr<dryengine::scene::Scene>& MenuScene();

    // ========================

    class IGameScene
    {
        public:
            virtual ~IGameScene() = default;

            uint32_t id;
            std::shared_ptr<dryengine::scene::Scene> scene;

        // TBD connection between scenes
    };
}