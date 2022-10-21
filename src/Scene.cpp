#include "../inc/Scene.hpp"

namespace dryengine
{
    namespace scene
    {
        const char *tag = "SCENE";

        void Scene::ProcessEvents(bool* state)
        {
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
            renderManager->Render();
        }

        void Scene::Update(double dt)
        {
            systemManager->UpdateSystems(dt);
        }

        Scene::Scene(SDL_Renderer* mainRenderer)
        {
            entityManager = std::make_shared<entitymgr::EntityManager>();
            componentManager = std::make_shared<componentmgr::ComponentManager>();
            systemManager = std::make_shared<systemmgr::SystemManager>(componentManager);
            renderManager = std::make_shared<rendermgr::RenderManager>(mainRenderer, componentManager);
            dataManager = std::make_shared<datamgr::DataManager>();
            eventManager = std::make_shared<eventmgr::EventManager>();

            componentManager->RegisterComponent<core::Transform>();
            componentManager->RegisterComponent<core::Graphics>();
            componentManager->RegisterComponent<core::Camera>();
            componentManager->RegisterComponent<core::LightSource>();

            renderManager->SetSignature<core::Transform>(rendermgr::RenderManagerSubsystem::RENDERER);
            renderManager->SetSignature<core::Transform>(rendermgr::RenderManagerSubsystem::LIGHTING);
            renderManager->SetSignature<core::Graphics>(rendermgr::RenderManagerSubsystem::RENDERER);
            renderManager->SetSignature<core::LightSource>(rendermgr::RenderManagerSubsystem::LIGHTING);
        }

        Scene::~Scene()
        {
            LOGI(tag, "Scene destroyed!");
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

        std::shared_ptr<systemmgr::SystemManager> &Scene::SystemManager()
        {
            return systemManager;
        }
        std::shared_ptr<entitymgr::EntityManager> &Scene::EntityManager()
        {
            return entityManager;
        }
        std::shared_ptr<eventmgr::EventManager> &Scene::EventManager()
        {
            return eventManager;
        }
        std::shared_ptr<rendermgr::RenderManager> &Scene::RenderManager()
        {
            return renderManager;
        }
        std::shared_ptr<datamgr::DataManager> &Scene::DataManager()
        {
            return dataManager;
        }
        std::shared_ptr<componentmgr::ComponentManager> &Scene::ComponentManager()
        {
            return componentManager;
        }
    }
}