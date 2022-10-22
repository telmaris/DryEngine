#include "../inc/Lakefields.hpp"

namespace lakefields
{
    
    auto lfengine = std::make_unique<dryengine::DryEngine>();

    auto mainmenu = CreateMainMenu(lfengine);

    void RunLakefields()
    {
        std::cout << "Lakefields launched";





        lfengine->loop();
    }
}

