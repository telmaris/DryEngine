#pragma once

#include "Utils.hpp"
#include "ComponentManager.hpp"

namespace dryengine
{
    namespace systems
    {
        class System
        {
        public:
            System(std::shared_ptr<componentmgr::ComponentManager> mgr);
            virtual void Update(double dt) = 0;

            virtual ~System();

            std::set<Entity> entityList;
            std::shared_ptr<componentmgr::ComponentManager> componentManager;
            Signature sig;
        };

        class CollisionSystem : public System
        {
        public:
            CollisionSystem(std::shared_ptr<componentmgr::ComponentManager> mgr);

            void Update(double dt) override;
        };

        class KinematicsSystem : public System
        {
        public:
            KinematicsSystem(std::shared_ptr<componentmgr::ComponentManager> mgr);

            void Update(double dt) override;
        };

        class ScriptSystem : public System
        {
        public:
            ScriptSystem(std::shared_ptr<componentmgr::ComponentManager> mgr);

            void Update(double dt) override;
        };

        class KeyboardSystem : public System
        {
        public:
            KeyboardSystem(std::shared_ptr<componentmgr::ComponentManager> mgr);

            void Update(double dt) override;
        };

        class MouseSystem : public System
        {
        public:
            MouseSystem(std::shared_ptr<componentmgr::ComponentManager> mgr);

            void Update(double dt) override;
        };

        class SoundSystem : public System
        {
        public:
            SoundSystem(std::shared_ptr<componentmgr::ComponentManager> mgr);

            void Update(double dt) override;
        };

    }
}