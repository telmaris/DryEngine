#include "../inc/SystemManager.hpp"

namespace dryengine
{
    namespace systemmgr
    {
        SystemManager::SystemManager(std::shared_ptr<componentmgr::ComponentManager>& cmgr)
        {
            componentManager = cmgr;
        }

        void SystemManager::EntityDestroyed(Entity e)
        {
            for (auto &i : systems)
            {
                auto const &sys = i.second;

                sys->entityList.erase(e);
            }
        }

        void SystemManager::EntitySignatureChanged(Entity e, Signature s)
        {
            for (auto const &p : systems)
            {
                auto const &n = p.first;
                auto const &sys = p.second;
                auto const &sysSig = systemSignatures[n];

                if ((s & sysSig) == sysSig)
                {
                    sys->entityList.insert(e);
                }
                else
                {
                    if (sys->entityList.find(e) != sys->entityList.end())
                    {
                        sys->entityList.erase(e);
                    }
                }
            }
        }

        void SystemManager::UpdateSystems(double dt)
        {
            for (auto &i : systems)
            {
                i.second->Update(dt);
            }
        }
    }
}