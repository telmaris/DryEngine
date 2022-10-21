//#include "inc/Engine.hpp"
#include "tests/Tests.hpp"


using namespace dryengine;
using namespace rendermgr;

//extern std::unique_ptr<DryEngine> engine;

int main()
{
    /*
    auto scene = engine->CreateScene();
    engine->ChangeScene(scene);

    auto bg = scene->CreateEntity();
    auto cam = scene->CreateEntity();
    auto l1 = scene->CreateEntity();
    auto l2 = scene->CreateEntity();
    
    scene->AddComponent<core::Transform>(bg, core::Transform{});
    scene->AddComponent<core::Graphics>(bg, core::Graphics{});

    scene->AddComponent<core::Camera>(cam,
     core::Camera{math::Vector2{WINDOW_SIZE_X,WINDOW_SIZE_Y}});
    scene->AddComponent<core::Transform>(cam, core::Transform{});

    scene->AddComponent<core::LightSource>(l1, core::LightSource{50, 30});
    scene->AddComponent<core::Transform>(l1, core::Transform{120, 100});
    auto tcomp = scene->GetComponent<core::Transform>(l1);
    auto lcomp = scene->GetComponent<core::LightSource>(l1);
    scene->AddComponent<core::LightSource>(l2, core::LightSource{300, -20});
    scene->AddComponent<core::Transform>(l2, core::Transform{250, 300});
    scene->RenderManager()->LoadGraphics(bg, "def.png");
    scene->RenderManager()->SetActiveCamera(cam);
    */
    int x = 5;
    
    Tests();

    return 0;
}   