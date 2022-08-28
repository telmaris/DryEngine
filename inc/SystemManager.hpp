#include "Utils.hpp"
#include "Systems.hpp"

namespace dryengine
{
    namespace systemmgr
    {
        class SystemManager
        {
        public:
            SystemManager();

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

            void UpdateSystems(double dt);

        private:
            std::map<const char *, Signature> systemSignatures;
            std::map<const char *, std::shared_ptr<systems::System>> systems;
        };
    }
}