#pragma once

#include "Utils.hpp"

namespace dryengine
{
    namespace entitymgr
    {
        class EntityManager
        {
        public:

		EntityManager();

		Entity CreateEntity();

		void DestroyEntity(Entity e);

		void SetSignature(Entity e, Signature s);

		Signature GetSignature(Entity e);

	private:

		std::queue<Entity> availableEntities;
		std::array<Signature, MAX_ENTITIES> entitiesArray;
		int entityCounter;
        };
    }
}