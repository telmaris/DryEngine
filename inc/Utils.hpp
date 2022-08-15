#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <chrono>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#undef main

#define WINDOW_SIZE_X 640
#define WINDOW_SIZE_Y 640

namespace dryengine
{
    void LOGI(const char* tag, const char* log);
    void LOGE(const char* tag, const char* log);
}