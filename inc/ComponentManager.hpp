#pragma once

#include "Utils.hpp"

namespace dryengine
{
    namespace componentmgr
    {
        class IComponentArray
        {
        public:
            virtual ~IComponentArray() = default;
            virtual void EntityDestroyed(Entity e) = 0;
        };

        template <typename T>
        class ComponentArray : public IComponentArray
        {
        public:
            void InsertData(Entity e, T c)
            {
                componentArray[e] = c;
                entityList.insert(e);
            }

            void RemoveData(Entity e)
            {
                componentArray[e] = T{};
                entityList.erase(e);
            }

            T &GetData(Entity e)
            {
                return componentArray[e];
            }

            void EntityDestroyed(Entity e) override
            {
                if (entityList.find(e) != entityList.end()) RemoveData(e);
            }

        private:
            std::array<T, MAX_ENTITIES> componentArray;
            std::set<Entity> entityList;
        };

        class ComponentManager
        {
        public:
            ComponentManager();

            template <typename T>
            void AddComponent(Entity e, T c)
            {
                GetComponentArray<T>()->InsertData(e, c);
            }

            template <typename T>
            void RemoveComponent(Entity e)
            {
                GetComponentArray<T>()->RemoveData(e);
            }

            template <typename T>
            void RegisterComponent()
            {
                const char *name = typeid(T).name();

                auto arr = std::make_shared<ComponentArray<T>>();

                componentTypes.insert({name, nextType});
                componentArrays.insert({name, arr});
                registeredComponents.set(nextType);

                ++nextType;
            }

            template <typename T>
            T &GetComponent(Entity e)
            {
                return GetComponentArray<T>()->GetData(e);
            }

            template <typename T>
            ComponentType GetComponentType()
            {
                const char *name = typeid(T).name();

                if (componentTypes.find(name) != componentTypes.end())
                {
                    return componentTypes[name];
                }
                else
                {
                    return NO_COMPONENT;
                }
            }

            void EntityDestroyed(Entity e);

            Signature GetComponentPool();

        private:
            std::map<const char *, ComponentType> componentTypes;
            std::map<const char *, std::shared_ptr<IComponentArray>> componentArrays;

            Signature registeredComponents;
            ComponentType nextType;

            template <typename T>
            std::shared_ptr<ComponentArray<T>> GetComponentArray()
            {
                const char *name = typeid(T).name();

                return std::static_pointer_cast<ComponentArray<T>>(componentArrays[name]);
            }
        };
    }
}