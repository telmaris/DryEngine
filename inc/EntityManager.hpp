#include "Utils.hpp"

namespace dryengine
{
    namespace entitymgr
    {
        class EntityManager
        {
        public:

		EntityManager()
		{
			entityCounter = 0;

			for (Entity e = 0; e < MAX_ENTITIES; e++)
			{
				availableEntities.push(e);
			}
		}

		Entity CreateEntity()
		{
			Entity ID = availableEntities.front();
			availableEntities.pop();
			entityCounter++;

			return ID;
		}

		void DestroyEntity(Entity e)
		{
			entitiesArray[e].reset();
			availableEntities.push(e);
			entityCounter--;
		}

		void SetSignature(Entity e, Signature s)
		{
			entitiesArray[e] = s;
		}

		Signature GetSignature(Entity e)
		{
			return entitiesArray[e];
		}


	private:

		std::queue<Entity> availableEntities;
		std::array<Signature, MAX_ENTITIES> entitiesArray;
		int entityCounter;
        };
    }
}