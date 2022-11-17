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
            Collider() = default;

            struct ColliderBox
            {
                int id;
                bool collide;
                bool isColliding;
                COLLISION collision;
                math::Vector2 size;
                math::Vector2 offset;
            };

            void AddColliderBox(math::Vector2 size, math::Vector2 pos = {}, bool active = true)
            {
                ColliderBox box{};
                box.collide = active;
                box.isColliding = false;
                box.collision = COLLISION::NONE;
                box.size = size;
                box.offset = pos;
                box.id = colliderBoxes.size();

                colliderBoxes.push_back(box);
            }

            //TODO:: add remove collider box mechanic

            std::vector<ColliderBox> colliderBoxes{};
            bool isColliding;
        };

        struct Graphics
        {
            enum class AnimationType : uint8_t
            {
                STATIC_TEXTURE = 0,
                MULTIPLE_TEXTURES = 1
            };

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
                    type = AnimationType::STATIC_TEXTURE;
                }

                Animation(std::string n, int s, int l, int ox, int oy, AnimationType t)
                {
                    name = n;
                    speed = s - 1;
                    length = l;
                    offsetX = ox;
                    offsetY = oy;
                    frame = 0;
                    type = t;
                }

                void Animate()
                {
                    frame = static_cast<int>((SDL_GetTicks() / (1 + speed)) % length);
                }

                std::string name;
                int speed = 0;
                int length;
                int offsetX, offsetY;
                int frame = 0;
                int textureID = 0;
                AnimationType type = AnimationType::STATIC_TEXTURE;
            };

            struct Texture
            {
                SDL_Texture *texture = NULL;
                math::Vector2 offset{};
                int x = 0, y = 0;
                bool visible = false;
                bool animated = false;
                int scale = 1;
                SDL_RendererFlip flip = SDL_FLIP_NONE;
            };

            Graphics() = default;

            void AddAnimation(std::string name, int speed, int len, int offx, int offy, AnimationType type)
            {
                animations.insert({name, std::make_shared<Animation>(name, speed, len, offx, offy, type)});
            }

            void RunAnimation(std::string n)
            {
                if (animations.find(n) != animations.end())
                {
                    currentAnimation = animations[n];
                    currentAnimation->frame = 0;
                }
            }

            void StopAnimation()
            {
                currentAnimation = nullptr;
            }

            void ClearGraphics()
            {
                if (!textures.empty())
                {
                    for(auto const& tex : textures)
                    {
                        SDL_DestroyTexture(tex.second.texture);
                    }
                }
            }

            void ShowTexture(int id, bool show)
            {
                if(textures.find(id) != textures.end())
                {
                    textures.at(id).visible = show;
                }
            }

            void AddTexture(int id, Texture tex)
            {
                if(textures.find(id) == textures.end())
                {
                    textures.insert({id, tex});
                }
            }

            void DeleteTexture(int id)
            {
                if(textures.find(id) != textures.end())
                {
                    textures.erase(id);
                }
            }

            std::map<int, Texture> textures;
            std::map<std::string, std::shared_ptr<Animation>> animations;
            std::shared_ptr<Animation> currentAnimation;
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

            Script(std::function<void(double dt, Entity e)> s)
            {
                script = s;
            }

            void SetState(bool state)
            {
                active = state;
            }

            std::function<void(double dt, Entity e)> script;

            bool active = true;
        };

        struct KeyboardController
        {
            KeyboardController()
            {
                script = nullptr;
            }

            KeyboardController(std::function<void(double t, Entity e, const Uint8 *keys, int dir)> s)
            {
                script = s;
            }

            void SetState(bool state)
            {
                active = state;
            }

            std::function<void(double dt, Entity e, const Uint8 *keys, int dir)> script;

            bool active = true;
        };

        struct MouseController
        {
            MouseController()
            {
                script = nullptr;
            }

            MouseController(std::function<void(double t, Entity e, int button, int x, int y)> s)
            {
                script = s;
            }

            void SetState(bool state)
            {
                active = state;
            }

            std::function<void(double dt, Entity e, int button, int x, int y)> script;

            bool active = true;
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

        struct LightSource
        {
            LightSource() : size({0,0}), temperature(0), intensity(0), 
                            offset(math::Vector2{0,0}) {}

            LightSource(math::Vector2 s, math::Vector2 off = {0,0}, int t = 255) : size(s), temperature(t),
             intensity(0), offset(off)  {}

            //uint32_t size;   //srednica kola(zrodla swiatla)
            int temperature;    // zaleznosc cieple-zimne
            uint8_t intensity;
            math::Vector2 offset;
            math::Vector2 size;
        };

    }
}