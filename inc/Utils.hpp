#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
//#include <chrono>
#include <bitset>
#include <queue>
#include <array>
#include <functional>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Maths.hpp"

#undef main

//#define WINDOW_SIZE_X 1440
//#define WINDOW_SIZE_Y 800

#define MAX_COMPONENTS 32
#define MAX_SCENES 32
#define MAX_ENTITIES 10000
#define NO_COMPONENT MAX_COMPONENTS

namespace dryengine
{
    using Entity = uint32_t;
	using Signature = std::bitset<MAX_COMPONENTS>;
	using ComponentType = uint8_t;
	using SceneID = uint8_t;
	using Geometry = SDL_Rect;
	
    using AudioEffect = Mix_Chunk;
	using Music = Mix_Music;

    enum class STATE
	{
		ON,
		OFF
	};

	enum class COLLISION
	{
		NONE,
		COLLISION_LEFT,
		COLLISION_RIGHT,
		COLLISION_UP,
		COLLISION_BOTTOM
	};

    void LOGI(const std::string& tag, const char* log);
    void LOGE(const std::string& tag, const char* log);
}