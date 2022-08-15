#include "inc/Engine.hpp"

int main()
{
    auto engine = std::make_unique<dryengine::DryEngine>();

    engine->loop();

    return 0;
}   