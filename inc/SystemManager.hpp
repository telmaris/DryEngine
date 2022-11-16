#pragma once

#include "Utils.hpp"
#include "Systems.hpp"
#include "ComponentManager.hpp"

namespace dryengine
{
    namespace systemmgr
    {
        class SystemManager
        {
        public:
            SystemManager(std::shared_ptr<componentmgr::ComponentManager>& cmgr);

            template <typename T>
            void RegisterSystem()
            {
                const char *name = typeid(T).name();

                auto s = componentManager->GetComponentPool();
                auto sys = std::make_shared<T>(componentManager);

                if ((sys->sig != 0) && ((sys->sig & s) == sys->sig))
                {
                    systems.insert({name, sys});
                    systemSignatures.insert({name, sys->sig});
                }
            }

            template <typename T>
            std::shared_ptr<systems::System> GetSystem()
            {
                const char *name = typeid(T).name();

                if(systems.find(name) != systems.end())
                {
                    return systems[name];
                }
                
                return nullptr;
            }

            void EntityDestroyed(Entity e);

            void EntitySignatureChanged(Entity e, Signature s);

            void UpdateSystems(double dt);

        private:
            std::shared_ptr<componentmgr::ComponentManager> componentManager;
            std::map<const char *, Signature> systemSignatures;
            std::unordered_map<const char *, std::shared_ptr<systems::System>> systems;
        };
    }
}