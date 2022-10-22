#include "../inc/Utils.hpp"

namespace dryengine
{
    void LOGI(const std::string& tag, const char* log)
    {
        std::cout << "-- LOG [" << tag << "]: " << log << std::endl;
    }

    void LOGE(const std::string& tag, const char* log)
    {
        std::cout << "-- ERROR [" << tag << "]: " << log << std::endl;
    }
}

