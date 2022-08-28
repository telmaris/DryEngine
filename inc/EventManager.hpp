#pragma once

#include "Utils.hpp"

namespace dryengine
{
    namespace eventmgr
    {
        class EventManager
        {
        public:
            //EventManager();

            bool KeyboardClick(const Uint8 *keyboard, int key);
            bool KeyboardRelease(const Uint8 *keyboard, int key);

            bool MouseClick(int button, SDL_Rect box);
            bool MouseRelease(int button, SDL_Rect box);

            void AddEvent(SDL_Event& e);
            void ClearEventVector();

        private:
            std::vector<SDL_Event> eventVector;
        };
    }
}