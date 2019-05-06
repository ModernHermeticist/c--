#pragma once
#ifndef MAIN_H
#define MAIN_H

extern "C"
{
#include "../sdl/include/SDL.h"
#include "../sdl/include/SDL_main.h"
}

#include <iostream>



#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int lanes = 14;

bool initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void closeSDL(SDL_Window* &window);

#endif