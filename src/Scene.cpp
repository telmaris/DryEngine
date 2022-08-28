#include "../inc/Scene.hpp"

namespace dryengine
{
    namespace scene
    {
        const char *tag = "SCENE";

        void Scene::ProcessEvents(bool* state)
        {
            LOGI(tag, "Processing events...");

            SDL_Event event = SDL_Event{};

            eventManager->ClearEventVector();

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    LOGI(tag, "Processing events found a quit!");
                    *state = false;
                    break;
                }

                eventManager->AddEvent(event);
            }
        }

        void Scene::Render()
        {
            
        }

        void Scene::Update(double dt)
        {
            systemManager->UpdateSystems(dt);
        }

        Scene::Scene()
        {
            entityManager = std::make_shared<entitymgr::EntityManager>();
            componentManager = std::make_shared<componentmgr::ComponentManager>();
            systemManager = std::make_shared<systemmgr::SystemManager>();
            renderManager = std::make_shared<rendermgr::RenderManager>();
            dataManager = std::make_shared<datamgr::DataManager>();
            eventManager = std::make_shared<eventmgr::EventManager>();
        }

        Entity Scene::CreateEntity()
        {
            return entityManager->CreateEntity();
        }

        void Scene::DestroyEntity(Entity e)
        {
            entityManager->DestroyEntity(e);
            componentManager->EntityDestroyed(e);
        }

        Signature Scene::GetSceneComponentPool()
        {
            return componentManager->GetComponentPool();
        }

        /* ========= Manager references ========= */

        constexpr std::shared_ptr<systemmgr::SystemManager> &Scene::SystemManager()
        {
            return systemManager;
        }
        constexpr std::shared_ptr<entitymgr::EntityManager> &Scene::EntityManager()
        {
            return entityManager;
        }
        constexpr std::shared_ptr<eventmgr::EventManager> &Scene::EventManager()
        {
            return eventManager;
        }
        constexpr std::shared_ptr<rendermgr::RenderManager> &Scene::RenderManager()
        {
            return renderManager;
        }
        constexpr std::shared_ptr<datamgr::DataManager> &Scene::DataManager()
        {
            return dataManager;
        }
        constexpr std::shared_ptr<componentmgr::ComponentManager> &Scene::ComponentManager()
        {
            return componentManager;
        }
    }
}