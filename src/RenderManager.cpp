#include "../inc/RenderManager.hpp"

namespace dryengine
{
    namespace rendermgr
    {
        RenderManager::RenderManager(SDL_Renderer *rend,
                                     std::shared_ptr<componentmgr::ComponentManager> &cmgr,
                                      int sizeX, int sizeY)
        {
            renderer = rend;
            componentManager = cmgr;
            camera = 0;
            windowSizeX = sizeX;
            windowSizeY = sizeY;
            if (rend != nullptr)
            {
                shadow = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_TARGET, windowSizeX, windowSizeY);

                SDL_SetTextureBlendMode(shadow, SDL_BLENDMODE_MOD);
            }

            tint = RGBALight{255, 255, 255, 255};
        }

        RenderManager::~RenderManager()
        {
        }

        void RenderManager::Render()
        {
            SDL_Rect dest{}, src{}, light{};

            auto const &ct = componentManager->GetComponent<core::Transform>(camera);
            auto const &cm = componentManager->GetComponent<core::Camera>(camera);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderTarget(renderer, shadow);
            SDL_SetRenderDrawColor(renderer, tint.r, tint.g, tint.b, tint.a); // render a tint
            SDL_RenderFillRect(renderer, nullptr);

            for (auto const &e : lightSourceList) // render all light points
            {
                auto const &t = componentManager->GetComponent<core::Transform>(e);
                auto const &l = componentManager->GetComponent<core::LightSource>(e);

                light.x = static_cast<int>((t.pos.x + l.offset.x - ct.pos.x) * (windowSizeX / cm.size.x)); // skalowanie
                light.y = static_cast<int>((t.pos.y + l.offset.y - ct.pos.y) * (windowSizeY / cm.size.y));
                light.w = static_cast<int>(l.size.x);
                light.h = static_cast<int>(l.size.y);
                SDL_SetRenderDrawColor(renderer, 200 + (l.temperature / 2), 200, 200 - (l.temperature / 2), 255);
                SDL_RenderFillRect(renderer, &light);
            }

            SDL_SetRenderTarget(renderer, nullptr);

            for (auto const &e : renderList)
            {
                auto const &t = componentManager->GetComponent<core::Transform>(e);
                auto &g = componentManager->GetComponent<core::Graphics>(e);

                SDL_Rect* ref = nullptr;

                if (g.currentAnimation)
                {
                    SDL_Rect src;
                    g.currentAnimation->Animate();

                    if(g.currentAnimation->type == core::Graphics::AnimationType::STATIC_TEXTURE)
                    {
                        auto x = g.textures.at(g.currentAnimation->textureID).x;
                        auto y = g.textures.at(g.currentAnimation->textureID).y;
                        src.x = g.currentAnimation->offsetX * x + g.currentAnimation->frame * x;
                        src.y = g.currentAnimation->offsetY * y;
                        src.w = x;
                        src.h = y;
                        ref = &src;
                    }
                    else
                    {
                        for(auto& tex : g.textures)
                        {
                            tex.second.visible = false;
                        }

                        g.textures.at(g.currentAnimation->textureID + g.currentAnimation->frame).visible = true;
                    }
                }

                for (auto const &tex : g.textures)
                {
                    if (tex.second.visible)
                    {
                        dest.x = (int)(t.pos.x - ct.pos.x) * (windowSizeX / cm.size.x); // skalowanie
                        dest.y = (int)(t.pos.y - ct.pos.y) * (windowSizeY / cm.size.y);
                        dest.w = tex.second.x * (windowSizeX / cm.size.x) * tex.second.scale;
                        dest.h = tex.second.y * (windowSizeY / cm.size.y) * tex.second.scale;
                        SDL_RenderCopyEx(renderer, tex.second.texture, ref, &dest, NULL, NULL, tex.second.flip);
                    }
                }
            }

            SDL_RenderCopy(renderer, shadow, nullptr, nullptr); // put the shadow on the main texture

            SDL_RenderPresent(renderer);
        }

        void RenderManager::LoadGraphics(Entity e, const char *p, int id, int scalearg,
                                         bool anim, int xarg, int yarg)
        {
            SDL_Surface *surf = NULL;
            SDL_Texture *texture = NULL;

            auto &gfx = componentManager->GetComponent<core::Graphics>(e);

            if (!(surf = IMG_Load(p)))
            {
                std::cout << "Failed to load surface.\n";
                std::cout << "SDL2 Error: " << SDL_GetError() << "\n";

                texture = NULL;
                return;
            }

            texture = SDL_CreateTextureFromSurface(renderer, surf);

            if (!texture)
            {
                std::cout << "Failed to create a texture.\n";
                std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
            }
            else
            {
                core::Graphics::Texture tex;

                SDL_TextureAccess a{};
                SDL_PixelFormatEnum f{};

                SDL_QueryTexture(texture, (Uint32 *)&f, (int *)&a, &tex.x, &tex.y);

                if (xarg != 0 && yarg != 0)
                {
                    tex.x = xarg;
                    tex.y = yarg;
                }

                tex.texture = texture;
                tex.animated = anim;
                tex.scale = scalearg;

                if(gfx.textures.empty())
                {
                    tex.visible = true;
                }

                gfx.textures.insert({id,tex});
            }

            SDL_FreeSurface(surf);
        }

        void RenderManager::SetActiveCamera(Entity e)
        {
            camera = e;
        }

        void RenderManager::SetCameraPosition(math::Vector2 pos)
        {
            auto &t = componentManager->GetComponent<core::Transform>(camera);
            t.pos = pos;
        }

        math::Vector2 const &RenderManager::GetCameraPosition()
        {
            return componentManager->GetComponent<core::Transform>(camera).pos;
        }

        math::Vector2 const &RenderManager::GetCameraSize()
        {
            return componentManager->GetComponent<core::Camera>(camera).size;
        }

        void RenderManager::AddAnimation(Entity e, std::string n, int s, int l, int ox, int oy, uint8_t type)
        {
            auto &gfx = componentManager->GetComponent<core::Graphics>(e);
            gfx.AddAnimation(n, s, l, ox, oy, static_cast<core::Graphics::AnimationType>(type));
        }

        void RenderManager::RunAnimation(Entity e, std::string name)
        {
            auto &gfx = componentManager->GetComponent<core::Graphics>(e);
            gfx.RunAnimation(name);
        }
    }
}