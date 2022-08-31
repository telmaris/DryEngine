#include "../inc/RenderManager.hpp"

namespace dryengine
{
    namespace rendermgr
    {
        RenderManager::RenderManager(SDL_Renderer *rend,
                                     std::shared_ptr<componentmgr::ComponentManager> &cmgr)
        {
            renderer = rend;
            componentManager = cmgr;
            camera = 0;
        }

        RenderManager::~RenderManager()
        {
        }

        void RenderManager::Render()
        {
            SDL_Rect dest{}, src{};

            auto const &ct = componentManager->GetComponent<core::Transform>(camera);
            auto const &cm = componentManager->GetComponent<core::Camera>(camera);

            SDL_RenderClear(renderer);

            for (auto const &e : entityList)
            {
                auto const &t = componentManager->GetComponent<core::Transform>(e);
                auto const &g = componentManager->GetComponent<core::Graphics>(e);

                dest.x = (int)(t.pos.x - ct.pos.x) * (WINDOW_SIZE_X / cm.size.x); // skalowanie
                dest.y = (int)(t.pos.y - ct.pos.y) * (WINDOW_SIZE_Y / cm.size.y);
                dest.w = g.x * (WINDOW_SIZE_X / cm.size.x) * g.scale;
                dest.h = g.y * (WINDOW_SIZE_Y / cm.size.y) * g.scale;

                if (g.visible)
                {
                    if (g.animated)
                    {
                        g.currentAnimation->Animate();
                        src.x = g.currentAnimation->offsetX * g.x + g.currentAnimation->frame * g.x;
                        src.y = g.currentAnimation->offsetY * g.y;
                        src.w = g.x;
                        src.h = g.y;
                        SDL_RenderCopyEx(renderer, g.texture, &src, &dest, NULL, NULL, g.flip);
                    }
                    else
                    {
                        SDL_RenderCopyEx(renderer, g.texture, NULL, &dest, NULL, NULL, g.flip);
                    }
                }
            }

            SDL_RenderPresent(renderer);
        }

        void RenderManager::LoadGraphics(Entity e, const char *p, int scalearg,
                                         bool a, int xarg, int yarg)
        {
            SDL_Surface *surf = NULL;
            SDL_Texture *texture;

            auto& gfx = componentManager->GetComponent<core::Graphics>(e);

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
                SDL_TextureAccess a{};
                SDL_PixelFormatEnum f{};

                SDL_QueryTexture(texture, (Uint32 *)&f, (int *)&a, &gfx.x, &gfx.y);

                if (xarg != 0 && yarg != 0)
                {
                    gfx.x = xarg;
                    gfx.y = yarg;
                }

                gfx.texture = texture;
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
    }
}