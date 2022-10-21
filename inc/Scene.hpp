#pragma once

#include "Utils.hpp"
#include "SystemManager.hpp"
#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "EventManager.hpp"
#include "RenderManager.hpp"
#include "DataManager.hpp"

namespace dryengine
{
    namespace scene
    {
        class Scene
        {
        public:
            void ProcessEvents(bool* state);
            void Render();
            void Update(double dt);

            Scene(SDL_Renderer* mainRenderer);

            ~Scene();

            Entity CreateEntity();

            void DestroyEntity(Entity e);

            template <typename T>
            void RegisterComponent()
            {
                componentManager->RegisterComponent<T>();
            }

            template <typename T>
            void AddComponent(Entity e, T c)
            {
                auto comp = componentManager->GetComponentType<T>();

                if (comp != NO_COMPONENT)
                {
                    componentManager->AddComponent(e, c);
                    auto sig = entityManager->GetSignature(e);

                    sig.set(comp);

                    entityManager->SetSignature(e, sig);
                    systemManager->EntitySignatureChanged(e, sig);
                    renderManager->EntitySignatureChanged(e, sig);
                }
            }

            template <typename T>
            void RemoveComponent(Entity e)
            {
                componentManager->RemoveComponent<T>(e);

                auto sig = entityManager->GetSignature(e);
                sig.set(componentManager->GetComponentType<T>(), false);
                entityManager->SetSignature(e, sig);

                systemManager->EntitySignatureChanged(e, sig);
            }

            template <typename T>
            ComponentType GetComponentType()
            {
                return componentManager->GetComponentType<T>();
            }

            template <typename T>
            T &GetComponent(Entity e)
            {
                return componentManager->GetComponent<T>(e);
            }

            template <typename T>
            void RegisterSystem()
            {
                systemManager->RegisterSystem<T>();
            }

        private:
            std::shared_ptr<systemmgr::SystemManager> systemManager;
            std::shared_ptr<entitymgr::EntityManager> entityManager;
            std::shared_ptr<eventmgr::EventManager> eventManager;
            std::shared_ptr<rendermgr::RenderManager> renderManager;
            std::shared_ptr<datamgr::DataManager> dataManager;
            std::shared_ptr<componentmgr::ComponentManager> componentManager;

            Signature GetSceneComponentPool();

        public:
            std::shared_ptr<systemmgr::SystemManager> &SystemManager();
            std::shared_ptr<entitymgr::EntityManager> &EntityManager();
            std::shared_ptr<eventmgr::EventManager> &EventManager();
            std::shared_ptr<rendermgr::RenderManager> &RenderManager();
            std::shared_ptr<datamgr::DataManager> &DataManager();
            std::shared_ptr<componentmgr::ComponentManager> &ComponentManager();

            uint8_t sceneID;
        };
    }
}