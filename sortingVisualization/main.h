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


#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int lanes = 200;
const int solveSpeed = 0;

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void closeSDL(SDL_Window*& window);
void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
bool bubbleSort(SDL_Renderer* renderer, std::vector<int>& v, int laneWidth);
bool selectionSort(SDL_Renderer* renderer, std::vector<int>& v, int laneWidth);
bool mergeSort(SDL_Renderer* renderer, std::vector<int>& v, int laneWidth, int l, int r);
void merge(std::vector<int>& v, int l, int m, int r);

#endif