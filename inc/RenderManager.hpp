#include "Utils.hpp"
#include "ComponentManager.hpp"

namespace dryengine
{
    namespace rendermgr
    {
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
            void SetSignature()
            {
                auto const &comtype = componentManager->GetComponentType<C>();
                signature.set(comtype);
            }

            void LoadGraphics(Entity e, const char *p, int scalearg = 1,
                              bool a = false, int xarg = 0, int yarg = 0);

            void EntitySignatureChanged(Entity e, Signature s)
            {

                if ((s & signature) == signature)
                {
                    entityList.insert(e);
                }
                else
                {
                    if (entityList.find(e) != entityList.end())
                    {
                        entityList.erase(e);
                    }
                }
            }
        private: 
        SDL_Renderer *renderer;
        Entity camera;
        std::shared_ptr<componentmgr::ComponentManager> componentManager;
        std::set<Entity> entityList;
        Signature signature;
        };
    }
}