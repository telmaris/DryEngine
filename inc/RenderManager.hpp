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
                          std::shared_ptr<componentmgr::ComponentManager> &cmgr);

            ~RenderManager();

            void Render();

            void SetActiveCamera(Entity e);
            void SetCameraPosition(math::Vector2 pos);
            math::Vector2 const &GetCameraPosition();
            math::Vector2 const &GetCameraSize();

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

            void LoadGraphics(Entity e, const char *p, int scalearg = 1,
                              bool a = false, int xarg = 0, int yarg = 0);

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

            void RenderManager::AddAnimation(Entity e, std::string n, int s, int l, int ox, int oy);
            void RenderManager::RunAnimation(Entity e, std::string name);
            
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

            bool lightsEnabled;
        };
    }
}