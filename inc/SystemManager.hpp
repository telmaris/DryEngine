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
            void RegisterSystem(Signature signature)
            {
                const char *name = typeid(T).name();

                auto sys = std::make_shared<T>(s);

                if ((sys->sig != 0) && ((sys->sig & signature) == sys->sig))
                {
                    systems.insert({name, sys});
                    systemSignatures.insert({name, sys->sig});
                }
            }

            void EntityDestroyed(Entity e);

            void EntitySignatureChanged(Entity e, Signature s);
            
            template<typename T, typename C> void SetSignature()
            {
                auto n = typeid.name(T);

                if(systems.find(n) != systems.end())
                {
                    auto const& syssig = systems[n]->sig;
                    auto const& comtype = componentManager->GetComponentType<C>();
                    signature.set(comtype);
                }
            }

            void UpdateSystems(double dt);

        private:
            std::shared_ptr<componentmgr::ComponentManager> componentManager;
            std::map<const char *, Signature> systemSignatures;
            std::unordered_map<const char *, std::shared_ptr<systems::System>> systems;
        };
    }
}