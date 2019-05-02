#pragma once
#ifndef MAIN_H
#define MAIN_H

extern "C"
{
#include "../lua/include/lua.h"
#include "../lua/include/lauxlib.h"
#include "../lua/include/lualib.h"
#include "../sdl/include/SDL.h"
#include "../sdl/include/SDL_main.h"
}

#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../sdl/include/SDL.h"
#include "spot.h"

#pragma comment(lib, "../lua/liblua53.a")
#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")


#endif

