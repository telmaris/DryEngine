#include "Utils.hpp"
#include "ComponentManager.hpp"

namespace dryengine
{
    namespace rendermgr
    {
        enum class RenderManagerSubsystem : uint8_t
        {
            RENDERER,
            LIGHTING
        };

        class RenderManager
        {
        public:
            RenderManager(SDL_Renderer *rend,
                          std::shared_ptr<componentmgr::ComponentManager> &cmgr,
                           int sizeX, int sizeY);

            ~RenderManager();

            void Render();

            // CAMERA

            void SetActiveCamera(Entity e);
            void SetCameraPosition(math::Vector2 pos);
            math::Vector2 const &GetCameraPosition();
            math::Vector2 const &GetCameraSize();

            // CORE

            template <typename C>
            void SetSignature(RenderManagerSubsystem s)
            {
                auto const &comtype = componentManager->GetComponentType<C>();
                switch (s)
                {
                case RenderManagerSubsystem::RENDERER:
                    renderSignature.set(comtype);
                    return;

                case RenderManagerSubsystem::LIGHTING:
                    lightSignature.set(comtype);
                    return;

                default:
                    return;
                }
            }

            void EntitySignatureChanged(Entity e, Signature s)
            {

                if ((s & renderSignature) == renderSignature)
                {
                    renderList.insert(e);
                }
                else
                {
                    if (renderList.find(e) != renderList.end())
                    {
                        renderList.erase(e);
                    }
                }
                if ((s & lightSignature) == lightSignature)
                {
                    lightSourceList.insert(e);
                }
                else
                {
                    if (lightSourceList.find(e) != lightSourceList.end())
                    {
                        lightSourceList.erase(e);
                    }
                }
            }

            // Loads and returns a raw SDL_Texture pointer
            SDL_Texture* ReturnTexture(const char *p);

            //Create empty texture of size [x,y]
            SDL_Texture* CreateTexture(int x, int y);

            // spritemap - Sprite map texture. size - {pos_x(in tiles), pos_y, size_x(in pixels), size_y}
            SDL_Texture* CutSprite(SDL_Texture* spritemap, Geometry size);

            // GRAPHICS & ANIMATION

            // Loads a ready Graphics component
            void LoadGraphics(Entity e, const char *p, int id, int scalearg = 1,
                              bool a = false, int xarg = 0, int yarg = 0);
            void RenderManager::AddAnimation(Entity e, std::string n, int s, int l, int ox, int oy, uint8_t type);
            void RenderManager::RunAnimation(Entity e, std::string name);
            
            // 

        private:
            struct RGBALight
            {
                RGBALight() = default;
                RGBALight(uint8_t red, uint8_t gr, uint8_t bl, uint8_t al) : r(red),
                        g(gr),
                        b(bl),
                        a(al) {}

                uint8_t r,g,b,a;
            };

            SDL_Renderer *renderer;
            SDL_Texture* shadow;
            RGBALight tint;
            Entity camera;
            std::shared_ptr<componentmgr::ComponentManager> componentManager;
            std::set<Entity> renderList;
            std::set<Entity> lightSourceList;
            Signature renderSignature;
            Signature lightSignature;

            int windowSizeX, windowSizeY;

            bool lightsEnabled;
        };
    }
}