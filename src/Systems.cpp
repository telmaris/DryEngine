
#include "../inc/Systems.hpp"

namespace dryengine
{
    namespace systems
    {
        System::System(std::shared_ptr<componentmgr::ComponentManager> mgr)
        {
            componentManager = mgr;
        }

        System::~System()
        {
        }

        /* COLLISION SYSTEM */

        CollisionSystem::CollisionSystem(std::shared_ptr<componentmgr::ComponentManager> mgr) : System(mgr)
        {
            auto tc = componentManager->GetComponentType<core::Transform>();
            auto cc = componentManager->GetComponentType<core::Collider>();

            if ((tc != NO_COMPONENT) && (cc != NO_COMPONENT))
            {
                sig.set(tc);
                sig.set(cc);
            }
        }

        void CollisionSystem::Update(double dt)
        {
            std::set<Entity> checked = entityList;

            for (auto const &e : entityList)
            {
                auto &c1 = componentManager->GetComponent<core::Collider>(e);
                c1.isColliding = false;
            }

            for (auto const &e : entityList)
            {
                auto &t1 = componentManager->GetComponent<core::Transform>(e);
                auto &c1 = componentManager->GetComponent<core::Collider>(e);

                SDL_Rect A = SDL_Rect{static_cast<int>(t1.pos.x), static_cast<int>(t1.pos.y), static_cast<int>(c1.size.x), static_cast<int>(c1.size.y)};

                checked.erase(e);

                for (auto const &f : checked)
                {
                    auto &t2 = componentManager->GetComponent<core::Transform>(f);
                    auto &c2 = componentManager->GetComponent<core::Collider>(f);

                    SDL_Rect B = SDL_Rect{static_cast<int>(t2.pos.x), static_cast<int>(t2.pos.y), static_cast<int>(c2.size.x), static_cast<int>(c2.size.y)};

                    SDL_Rect collisionRect;

                    if (SDL_IntersectRect(&A, &B, &collisionRect))
                    {
                        auto &rb1 = componentManager->GetComponent<core::RigidBody>(e);
                        auto &rb2 = componentManager->GetComponent<core::RigidBody>(f);
                        c1.isColliding = true;
                        c2.isColliding = true;

                        if (collisionRect.w >= collisionRect.h)
                        {
                            // top/bottom

                            if (collisionRect.y == t1.pos.y)
                            {
                                t2.pos.y += t1.pos.y - (t2.pos.y + c2.size.y);
                            }
                            else
                            {
                                t2.pos.y += t1.pos.y - (t2.pos.y + c1.size.y);
                            }
                        }
                        else
                        {
                            // left/right

                            if (collisionRect.x == t1.pos.x)
                            {
                                t2.pos.x += t1.pos.x - (t2.pos.x + c2.size.x);
                            }
                            else
                            {
                                t2.pos.x += t1.pos.x - (t2.pos.x + c1.size.x);
                            }
                        }
                    }
                }
            }
        }

        /* KINEMATICS SYSTEM */

        KinematicsSystem::KinematicsSystem(std::shared_ptr<componentmgr::ComponentManager> mgr) : System(mgr)
        {
            auto tc = componentManager->GetComponentType<core::Transform>();
            auto rc = componentManager->GetComponentType<core::RigidBody>();

            if ((tc != NO_COMPONENT) && (rc != NO_COMPONENT))
            {
                sig.set(tc);
                sig.set(rc);
            }
        }

        void KinematicsSystem::Update(double dt)
        {
            for (auto const &e : entityList)
            {
                auto &t = componentManager->GetComponent<core::Transform>(e);
                auto &r = componentManager->GetComponent<core::RigidBody>(e);

                r.vel += r.acc * dt;
                t.pos += r.vel * dt;
            }
        }

        /* SCRIPT SYSTEM */

        ScriptSystem::ScriptSystem(std::shared_ptr<componentmgr::ComponentManager> mgr) : System(mgr)
        {
            auto sc = componentManager->GetComponentType<core::Script>();

            if ((sc != NO_COMPONENT))
            {
                sig.set(sc);
            }
        }

        void ScriptSystem::Update(double dt)
        {
            for (auto const &e : entityList)
            {
                auto const &sc = componentManager->GetComponent<core::Script>(e);

                sc.script(dt, e);
            }
        }

        /* KEYBOARD SYSTEM */

        KeyboardSystem::KeyboardSystem(std::shared_ptr<componentmgr::ComponentManager> mgr) : System(mgr)
        {
            auto tc = componentManager->GetComponentType<core::KeyboardController>();

            if (tc != NO_COMPONENT)
            {
                sig.set(tc);
            }
        }

        void KeyboardSystem::Update(double dt)
        {
            const Uint8 *key = SDL_GetKeyboardState(nullptr);

            for (auto const &e : entityList)
            {
                auto const &kc = componentManager->GetComponent<core::KeyboardController>(e);

                kc.script(dt, e, key, 1);
            }
        }

        /* MOUSE SYSTEM */

        MouseSystem::MouseSystem(std::shared_ptr<componentmgr::ComponentManager> mgr) : System(mgr)
        {
            auto mc = componentManager->GetComponentType<core::MouseController>();

            if (mc != NO_COMPONENT)
            {
                sig.set(mc);
            }
        }

        void MouseSystem::Update(double dt)
        {
            int x, y;
            Uint32 button = SDL_GetMouseState(&x, &y);

            for (auto const &e : entityList)
            {
                auto const &mc = componentManager->GetComponent<core::MouseController>(e);

                mc.script(dt, e, button, x, y);
            }
        }

        /* SOUND SYSTEM */

        SoundSystem::SoundSystem(std::shared_ptr<componentmgr::ComponentManager> mgr) : System(mgr)
        {
            auto snd = componentManager->GetComponentType<core::Sound>();

            if (snd != NO_COMPONENT)
            {
                sig.set(snd);
            }
        }

        void SoundSystem::Update(double dt)
        {
            for (auto const &e : entityList)
            {
                auto &const snd = componentManager->GetComponent<core::Sound>(e);

                for (auto i = 0; i < snd.source.states.size(); i++)
                {
                    if (snd.source.states[i] == STATE::ON)
                    {
                        Mix_PlayChannel(-1, snd.source.tracks[i], 0);
                    }
                    else
                    {
                        // TODO:
                    }
                }

                for (auto i = 0; i < snd.themes.states.size(); i++)
                {
                    /*if (snd.themes.states[i] == e2dSTATE::ON)
                    {
                        if (Mix_PlayMusic(snd.themes.tracks[i], 0) < 0)
                        {
                            std::cout << "Error playing the music: " << Mix_GetError() << std::endl;
                        }
                    }
                    else
                    {
                        Mix_PauseMusic();
                    }*/
                }
            }
        }
    }
    /*
    int SystemManager::AddMusic(Entity e, const char* title)
    {
        auto& snd = scene->GetComponent<Sound>(e);

        int id = snd.themes.states.size();

        if (auto mus = Mix_LoadMUS(title))
        {
            snd.themes.tracks.push_back(mus);
            snd.themes.states.push_back(e2dSTATE::OFF);
        }
        else
        {
            std::cout << "A problem occured when loading mp3.\n";
            std::cout << SDL_GetError() << std::endl;
            return -1;
        }

        return id;
    }

    int SystemManager::AddSoundEffect(Entity e, const char* title)
    {
        auto& snd = scene->GetComponent<Sound>(e);

        int id = snd.source.states.size();

        snd.source.tracks.push_back(Mix_LoadWAV(title));
        snd.source.states.push_back(e2dSTATE::OFF);

        return id;
    }

    void SystemManager::PlayMusic(Entity e, int id)
    {
        auto& snd = scene->GetComponent<Sound>(e);

        //snd.themes.states[id] = e2dSTATE::ON;

        if (Mix_PlayMusic(snd.themes.tracks[id], 0) < 0)
        {
            std::cout << "Error playing the music: " << Mix_GetError() << std::endl;
        }
    }

    void SystemManager::PlaySoundEffect(Entity e, int id)
    {
        auto& snd = scene->GetComponent<Sound>(e);

        //snd.source.states[id] = e2dSTATE::ON;

        Mix_PlayChannel(-1, snd.source.tracks[id], 0);
    }

    void SystemManager::StopMusic(Entity e, int id)
    {
        auto& snd = scene->GetComponent<Sound>(e);

        //snd.themes.states[id] = e2dSTATE::OFF;

        Mix_PauseMusic();
    }

    void SystemManager::StopSoundEffect(Entity e, int id)
    {
        auto& snd = scene->GetComponent<Sound>(e);

        //snd.source.states[id] = e2dSTATE::OFF;
    }*/

    /* PLAIN SYSTEM */

}
