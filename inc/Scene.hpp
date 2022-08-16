#pragma once

#include "Utils.hpp"
#include "SystemManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "RenderManager.hpp"

namespace dryengine
{
    namespace scene
    {
        class Scene
        {
        public:
            Scene();

            

        private:
            std::unique_ptr<systemmgr::SystemManager> systemManager;
            std::unique_ptr<entitymgr::EntityManager> entityManager;
            std::unique_ptr<componentmgr::ComponentManager> componentManager;
            std::unique_ptr<eventmgr::EventManager> eventManager;
            std::unique_ptr<rendermgr::RenderManager> renderManager;
        };
    }
}