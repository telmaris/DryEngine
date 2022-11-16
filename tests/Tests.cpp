#include "Tests.hpp"

namespace dryengine
{

    std::unique_ptr<DryEngine> engine = std::make_unique<DryEngine>();

    auto s1 = engine->CreateScene(0);

    auto map1 = s1->CreateEntity();
    auto map2 = s1->CreateEntity();
    auto map3 = s1->CreateEntity();
    auto map4 = s1->CreateEntity();

    auto platform1 = s1->CreateEntity();
    auto platform2 = s1->CreateEntity();
    auto platform3 = s1->CreateEntity();
    auto platform4 = s1->CreateEntity();

    auto dino = s1->CreateEntity();

    auto camera = s1->CreateEntity();

    void DinoScript(double dt, Entity e)
    {
        auto &rb = s1->GetComponent<core::RigidBody>(e);
        auto &gfx = s1->GetComponent<core::Graphics>(e);
        auto const &collider = s1->GetComponent<core::Collider>(e);

        if (collider.isColliding)
        {
            rb.acc = {0, 0};
            // rb.vel = { 0, 0 };
        }
        else
        {
            rb.acc = {0, 900};
        }

        if (rb.vel.x < 0)
        {
            gfx.textures[0].flip = SDL_FLIP_HORIZONTAL;
        }
        else
        {
            gfx.textures[0].flip = SDL_FLIP_NONE;
        }

        if (abs(rb.vel.x) > 0)
        {
            s1->RenderManager()->RunAnimation(e, "walk");
        }
        else
        {
            s1->RenderManager()->RunAnimation(e, "stand");
        }
    }

    void KeyboardTestScript(double dt, Entity e, const Uint8 *keys, int dir)
    {
        auto &collider = s1->GetComponent<core::Collider>(e);
        auto &rb = s1->GetComponent<core::RigidBody>(e);

        rb.vel.x = (keys[SDL_SCANCODE_D] * 200) - (keys[SDL_SCANCODE_A] * 200);
        // rb.vel.y = (keys[SDL_SCANCODE_S] * 200) - (keys[SDL_SCANCODE_W] * 200);

        if (s1->EventManager()->KeyboardClick(keys, SDLK_SPACE) && collider.isColliding)
        {
            rb.vel.y = -500;
        }
    }

    void mscript(double dt, Entity e, int button, int x, int y)
    {
        auto &t = s1->GetComponent<core::Transform>(e);

        SDL_Rect box = SDL_Rect{static_cast<int>(t.pos.x), static_cast<int>(t.pos.y), 100, 100};

        if (s1->EventManager()->MouseClick(1, box))
        {
            std::cout << "Clicked!\n";
            // s1->PlaySoundEffect(e, 0);
        }
    }

    void cameraScript(double dt, Entity e)
    {
        auto &tCamera = s1->GetComponent<core::Transform>(e);
        auto const &tDino = s1->GetComponent<core::Transform>(dino);

        tCamera.pos.x = tDino.pos.x - (s1->RenderManager()->GetCameraSize().x / 2);
    }

    void mapScript(double dt, Entity e)
    {
        auto &const tCamera = s1->GetComponent<core::Transform>(camera);
        auto &tMap = s1->GetComponent<core::Transform>(e);
        auto &gMap = s1->GetComponent<core::Graphics>(e);

        if (tMap.pos.x + gMap.textures[0].x < tCamera.pos.x)
        {
            tMap.pos.x += 1920;
        }
        if (tMap.pos.x > tCamera.pos.x + s1->RenderManager()->GetCameraSize().x)
        {
            tMap.pos.x -= 1920;
        }
    }

    void Tests()
    {
        engine->ChangeScene(0);

        s1->RenderManager()->SetActiveCamera(camera);

        s1->AddComponent(camera, core::Transform{0, 0});
        s1->AddComponent(camera, core::Camera{math::Vector2{1440, 800}});
        s1->AddComponent(camera, core::Script{cameraScript});

        // std::cout << s1->GetCameraPosition() << std::endl;
        // std::cout << s1->RenderManager()->GetCameraSize() << std::endl;

        s1->AddComponent(map1, core::Transform{0, 0});
        s1->AddComponent(map1, core::Graphics{});
        s1->RenderManager()->LoadGraphics(map1, "assets/bg.png", 0);
        s1->AddComponent(map1, core::Script{mapScript});

        s1->AddComponent(map2, core::Transform{480, 0});
        s1->AddComponent(map2, core::Graphics{});
        s1->RenderManager()->LoadGraphics(map2, "assets/bg.png", 0);
        s1->AddComponent(map2, core::Script{mapScript});

        s1->AddComponent(map3, core::Transform{960, 0});
        s1->AddComponent(map3, core::Graphics{});
        s1->RenderManager()->LoadGraphics(map3, "assets/bg.png", 0);
        s1->AddComponent(map3, core::Script{mapScript});

        s1->AddComponent(map4, core::Transform{1440, 0});
        s1->AddComponent(map4, core::Graphics{});
        s1->RenderManager()->LoadGraphics(map4, "assets/bg.png", 0);
        s1->AddComponent(map4, core::Script{mapScript});

        s1->AddComponent(platform1, core::Transform{0, 600});
        s1->AddComponent(platform1, core::Graphics{});
        s1->RenderManager()->LoadGraphics(platform1, "assets/platform.png", 0, 4, true, 128, 16);
        s1->AddComponent(platform1, core::RigidBody{math::Vector2{0, 0}, math::Vector2{0, 0}});
        s1->AddComponent(platform1, core::Collider{});
        s1->GetComponent<core::Collider>(platform1).AddColliderBox(math::Vector2{512, 64});
        s1->RenderManager()->AddAnimation(platform1, "platform", 1, 1, 0, 1, 0);
        s1->RenderManager()->RunAnimation(platform1, "platform");
        s1->AddComponent(platform1, core::LightSource{{512, 64}, {0, -5}, 0});

        s1->AddComponent(platform2, core::Transform{650, 540});
        s1->AddComponent(platform2, core::Graphics{});
        s1->RenderManager()->LoadGraphics(platform2, "assets/platform.png", 0, 4, true, 128, 16);
        s1->AddComponent(platform2, core::RigidBody{math::Vector2{0, 0}, math::Vector2{0, 0}});
        s1->AddComponent(platform2, core::Collider{});
        s1->GetComponent<core::Collider>(platform2).AddColliderBox(math::Vector2{512, 64});
        s1->RenderManager()->AddAnimation(platform2, "platform", 1, 1, 0, 1, 0);
        s1->RenderManager()->RunAnimation(platform2, "platform");
        s1->AddComponent(platform2, core::LightSource{{512, 64}, {0, -5}, 0});

        s1->AddComponent(platform3, core::Transform{1300, 640});
        s1->AddComponent(platform3, core::Graphics{});
        s1->RenderManager()->LoadGraphics(platform3, "assets/platform.png", 0, 4, true, 128, 16);
        s1->AddComponent(platform3, core::RigidBody{math::Vector2{0, 0}, math::Vector2{0, 0}});
        s1->AddComponent(platform3, core::Collider{});
        s1->GetComponent<core::Collider>(platform3).AddColliderBox(math::Vector2{512, 64});
        s1->RenderManager()->AddAnimation(platform3, "platform", 1, 1, 0, 1, 0);
        s1->RenderManager()->RunAnimation(platform3, "platform");
        s1->AddComponent(platform3, core::LightSource{{512, 64}, {0, -5}, 0});

        s1->AddComponent(platform4, core::Transform{1850, 580});
        s1->AddComponent(platform4, core::Graphics{});
        s1->RenderManager()->LoadGraphics(platform4, "assets/platform.png", 0, 4, true, 128, 16);
        s1->AddComponent(platform4, core::RigidBody{math::Vector2{0, 0}, math::Vector2{0, 0}});
        s1->AddComponent(platform4, core::Collider{});
        s1->GetComponent<core::Collider>(platform4).AddColliderBox(math::Vector2{512, 64});
        s1->RenderManager()->AddAnimation(platform4, "platform", 1, 1, 0, 1, 0);
        s1->RenderManager()->RunAnimation(platform4, "platform");
        s1->AddComponent(platform4, core::LightSource{{512, 64}, {0, -5}, 0});

        s1->AddComponent(dino, core::Transform{121, 300});
        s1->AddComponent(dino, core::RigidBody{math::Vector2{0, 900}, math::Vector2{0, 0}});
        s1->AddComponent(dino, core::Collider{});
        s1->GetComponent<core::Collider>(dino).AddColliderBox(math::Vector2{120,120});
        s1->AddComponent(dino, core::Graphics{});
        s1->RenderManager()->LoadGraphics(dino, "assets/dino.png", 0, 5, true, 24, 24);

        s1->RenderManager()->AddAnimation(dino, "walk", 100, 6, 4, 0, 0);
        s1->RenderManager()->AddAnimation(dino, "stand", 100, 4, 0, 0, 0);
        s1->RenderManager()->RunAnimation(dino, "stand");

        s1->AddComponent(dino, core::Script{DinoScript});
        s1->AddComponent(dino, core::KeyboardController{KeyboardTestScript});
        s1->AddComponent(dino, core::MouseController{mscript});
        s1->AddComponent(dino, core::Sound{});
        s1->AddComponent(dino, core::LightSource{{120,120}, {0, 0}, 0});

        // auto music = s1->AddSoundEffect(dino, "gtr.wav");

        engine->loop();
    }
}
