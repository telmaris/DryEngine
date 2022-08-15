#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <chrono>

#include <SDL.h>

#undef main

namespace dryengine
{
    void LOGI(const char* tag, const char* log);
    void LOGE(const char* tag, const char* log);
}