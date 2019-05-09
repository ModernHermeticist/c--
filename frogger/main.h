#pragma once
#ifndef MAIN_H
#define MAIN_H

extern "C"
{
#include "../sdl/include/SDL.h"
#include "../sdl/include/SDL_main.h"
}

#include <iostream>
#include <vector>
#include "Cell.h"



#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int lanes = 14;

const int CELL_SIZE = SCREEN_WIDTH / lanes;

enum KeyCodes{Exit, Up, Left, Right, Down};

bool initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void closeSDL(SDL_Window* &window);
void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool fill);
void drawBackground(SDL_Renderer* renderer, int laneHeight);
int parseInput();

#endif