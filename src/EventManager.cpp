#include "../inc/EventManager.hpp"

namespace dryengine
{
    namespace eventmgr
    {
        void EventManager::AddEvent(SDL_Event &e)
        {
            eventVector.push_back(e);
        }

        void EventManager::ClearEventVector()
        {
            eventVector.clear();
        }

        bool EventManager::KeyboardClick(const Uint8 *keyboard, int key)
        {
            for (auto const& e : eventVector)
            {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == key && e.key.repeat == 0)
                {
                    std::cout << "Key clicked!\n";
                    return true;
                }
            }

            return false;
        }

        bool EventManager::KeyboardRelease(const Uint8 *keyboard, int key)
        {
            for (auto const& e : eventVector)
            {
                if (e.type == SDL_KEYUP && e.key.keysym.sym == key && e.key.repeat == 0)
                {
                    std::cout << "Key released!\n";
                    return true;
                }
            }

            return false;
        }

        bool EventManager::MouseClick(int button, SDL_Rect box)
        {
            for (auto const& e : eventVector)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == button && (e.button.x >= box.x && e.button.x <= (box.x + box.w)) && (e.button.y >= box.y && e.button.y <= (box.y + box.h)))
                {
                    std::cout << "Mouse clicked!\n";
                    return true;
                }
            }

            return false;
        }

        bool EventManager::MouseRelease(int button, SDL_Rect box)
        {
            for (auto const& e : eventVector)
            {
                if (e.type == SDL_MOUSEBUTTONUP && e.button.button == button && (e.button.x >= box.x && e.button.x <= (box.x + box.w)) && (e.button.y >= box.y && e.button.y <= (box.y + box.h)))
                {
                    std::cout << "Mouse released!\n";
                    return true;
                }
            }

            return false;
        }
    }
}