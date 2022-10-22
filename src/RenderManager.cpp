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
            if (rend != nullptr)
            {
                shadow = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_TARGET, WINDOW_SIZE_X, WINDOW_SIZE_Y);

                SDL_SetTextureBlendMode(shadow, SDL_BLENDMODE_MOD);
            }

            tint = RGBALight{80,80,150,255};
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
            SDL_SetRenderDrawColor(renderer, tint.r, tint.g, tint.b, tint.a);   // render a tint
            SDL_RenderFillRect(renderer, nullptr);

            for (auto const &e : lightSourceList)   // render all light points
            {
                auto const &t = componentManager->GetComponent<core::Transform>(e);
                auto const &l = componentManager->GetComponent<core::LightSource>(e);

                light.x = static_cast<int>((t.pos.x + l.offset.x - ct.pos.x) * (WINDOW_SIZE_X / cm.size.x)); // skalowanie
                light.y = static_cast<int>((t.pos.y + l.offset.y - ct.pos.y) * (WINDOW_SIZE_Y / cm.size.y));
                light.w = static_cast<int>(l.size.x);
                light.h = static_cast<int>(l.size.y);
                SDL_SetRenderDrawColor(renderer, 200 + (l.temperature/2), 200, 200 - (l.temperature/2), 255);
                SDL_RenderFillRect(renderer, &light);
            }

            SDL_SetRenderTarget(renderer, nullptr);

            for (auto const &e : renderList)
            {
                auto const &t = componentManager->GetComponent<core::Transform>(e);
                auto const &g = componentManager->GetComponent<core::Graphics>(e);

                if (g.visible)
                {
                    dest.x = (int)(t.pos.x - ct.pos.x) * (WINDOW_SIZE_X / cm.size.x); // skalowanie
                    dest.y = (int)(t.pos.y - ct.pos.y) * (WINDOW_SIZE_Y / cm.size.y);
                    dest.w = g.x * (WINDOW_SIZE_X / cm.size.x) * g.scale;
                    dest.h = g.y * (WINDOW_SIZE_Y / cm.size.y) * g.scale;

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

            SDL_RenderCopy(renderer, shadow, nullptr, nullptr); //put the shadow on the main texture

            SDL_RenderPresent(renderer);
        }

        void RenderManager::LoadGraphics(Entity e, const char *p, int scalearg,
                                         bool anim, int xarg, int yarg)
        {
            SDL_Surface *surf = NULL;
            SDL_Texture *texture;

            auto &gfx = componentManager->GetComponent<core::Graphics>(e);
            gfx.scale = scalearg;

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

                //SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);
                gfx.texture = texture;
                gfx.animated = anim;
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

        void RenderManager::AddAnimation(Entity e, std::string n, int s, int l, int ox, int oy)
		{
            auto& gfx = componentManager->GetComponent<core::Graphics>(e);
			gfx.AddAnimation(n, s, l, ox, oy);
		}

		void RenderManager::RunAnimation(Entity e, std::string name)
		{
			auto& gfx = componentManager->GetComponent<core::Graphics>(e);
			gfx.RunAnimation(name);
		}
    }
}