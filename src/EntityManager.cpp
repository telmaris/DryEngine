#include "../inc/EntityManager.hpp"

namespace dryengine
{
    namespace entitymgr
    {
        EntityManager::EntityManager()
		{
			entityCounter = 0;

			for (Entity e = 0; e < MAX_ENTITIES; e++)
			{
				availableEntities.push(e);
			}
		}

		Entity EntityManager::CreateEntity()
		{
			Entity ID = availableEntities.front();
			availableEntities.pop();
			entityCounter++;

			return ID;
		}

		void EntityManager::DestroyEntity(Entity e)
		{
			entitiesArray[e].reset();
			availableEntities.push(e);
			entityCounter--;
		}

		void EntityManager::SetSignature(Entity e, Signature s)
		{
			entitiesArray[e] = s;
		}

		Signature EntityManager::GetSignature(Entity e)
		{
			return entitiesArray[e];
		}
    }
}