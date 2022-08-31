#include "inc/Engine.hpp"

dryengine::DryEngine engine{};

using namespace dryengine;
using namespace rendermgr;

int main()
{
    auto scene = engine.CreateScene();
    engine.ChangeScene(scene);

    auto bg = scene->CreateEntity();
    auto cam = scene->CreateEntity();
    
    scene->AddComponent<core::Transform>(bg, core::Transform{});
    scene->AddComponent<core::Graphics>(bg, core::Graphics{});
    scene->AddComponent<core::Camera>(cam, core::Camera{math::Vector2{640,640}});
    scene->AddComponent<core::Transform>(cam, core::Transform{});
    scene->RenderManager()->LoadGraphics(bg, "def.png");
    scene->RenderManager()->SetActiveCamera(cam);

    engine.loop();

    return 0;
}   