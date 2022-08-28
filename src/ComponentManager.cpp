#include "../inc/ComponentManager.hpp"

namespace dryengine
{
    namespace componentmgr
    {
        ComponentManager::ComponentManager()
        {
            nextType = 0;
        }

        void ComponentManager::EntityDestroyed(Entity e)
        {
            for (auto const &i : componentArrays)
            {
                i.second->EntityDestroyed(e);
            }
        }

        Signature ComponentManager::GetComponentPool()
        {
            return registeredComponents;
        }
    }
}