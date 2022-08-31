#pragma once

#include "Utils.hpp"

namespace dryengine
{
    namespace core
    {
        struct Transform
        {
            Transform()
            {
                pos.x = 0;
                pos.y = 0;
            }

            Transform(double a, double b)
            {
                pos.x = a;
                pos.y = b;
            }

            math::Vector2 pos;
        };

        struct RigidBody
        {
            RigidBody()
            {
                acc = {};
                vel = {};
            }

            RigidBody(math::Vector2 a, math::Vector2 v)
            {
                acc = a;
                vel = v;
            }

            math::Vector2 acc, vel;
        };

        struct Collider
        {
            Collider(math::Vector2 s, bool c = true)
            {
                collide = c;
                isColliding = false;
                collision = COLLISION::NONE;
                size.x = s.x;
                size.y = s.y;
            }

            Collider()
            {
                collide = false;
                isColliding = false;
                collision = COLLISION::NONE;
                size.x = 0;
                size.y = 0;
            }

            bool collide;
            bool isColliding;
            COLLISION collision;
            math::Vector2 size;
        };

        struct Graphics
        {
            struct Animation
            {
            public:
                Animation()
                {
                    name = {};
                    speed = 0;
                    length = 1;
                    offsetX = 0;
                    offsetY = 0;
                    frame = 0;
                }

                Animation(std::string n, int s, int l, int ox, int oy)
                {
                    name = n;
                    speed = s - 1;
                    length = l;
                    offsetX = ox;
                    offsetY = oy;
                    frame = 0;
                }

                void Animate()
                {
                    frame = static_cast<int>((SDL_GetTicks() / (1 + speed)) % length);
                }

                std::string name;
                int speed;
                int length;
                int offsetX, offsetY;
                int frame;
            };

            Graphics()
            {
                texture = NULL;
                x = 0;
                y = 0;
                visible = true;
                animated = false;
                flip = SDL_FLIP_NONE;
                scale = 1;
            }

            void AddAnimation(std::string name, int speed, int len, int offx, int offy)
            {
                animations.insert({name, std::make_shared<Animation>(name, speed, len, offx, offy)});
            }

            void RunAnimation(std::string n)
            {
                if (animations.find(n) != animations.end())
                {
                    currentAnimation = animations[n];
                    currentAnimation->frame = 0;
                }
            }

            void ClearGraphics()
            {
                if (texture)
                {
                    SDL_DestroyTexture(texture);
                }
            }

            SDL_Texture *texture;
            int x, y;
            bool visible;
            bool animated;
            int scale;
            std::map<std::string, std::shared_ptr<Animation>> animations;
            std::shared_ptr<Animation> currentAnimation;
            SDL_RendererFlip flip;
        };

        struct Camera
        {
            Camera()
            {
                size = math::Vector2{};
                zoom = 1.0;
                active = false;
            }

            Camera(math::Vector2 s, double z = 1.0)
            {
                size = s;
                zoom = z;
                active = true;
            }

            math::Vector2 size;
            double zoom;

            bool active;
        };

        struct Script
        {
            Script()
            {
                script = nullptr;
            }

            Script(void (*s)(double dt, Entity e))
            {
                script = s;
            }

            std::function<void(double dt, Entity e)> script;
        };

        struct KeyboardController
        {
            KeyboardController()
            {
                script = nullptr;
            }

            KeyboardController(void (*s)(double t, Entity e, const Uint8 *keys, int dir))
            {
                script = s;
            }

            std::function<void(double dt, Entity e, const Uint8 *keys, int dir)> script;
        };

        struct MouseController
        {
            MouseController()
            {
                script = nullptr;
            }

            MouseController(void (*s)(double t, Entity e, int button, int x, int y))
            {
                script = s;
            }

            std::function<void(double dt, Entity e, int button, int x, int y)> script;
        };

        struct Sound
        {
            struct AudioSource
            {
                std::vector<AudioEffect*> tracks;
                std::vector<STATE> states;
            };

            struct MusicThemes
            {
                std::vector<Music*> tracks;
                std::vector<STATE> states;
            };

            Sound()
            {
                source = AudioSource{};
                themes = MusicThemes{};
            }

            void ClearSound()
            {
                for (auto &t : source.tracks)
                {
                    Mix_FreeChunk(t);
                }
                for (auto &t : themes.tracks)
                {
                    Mix_FreeMusic(t);
                }
                source.tracks.clear();
                source.states.clear();
                themes.tracks.clear();
                themes.states.clear();
            }

            AudioSource source;
            MusicThemes themes;
        };

    }
}