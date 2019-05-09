#pragma once
#ifndef MAIN_H
#define MAIN_H

extern "C"
{
#include "../sdl/include/SDL.h"
#include "../sdl/include/SDL_main.h"
}

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Snake.h"


#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")


enum KeyCodes{quit, GoLeft, GoRight, GoUp, GoDown};


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int cells = 25;

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void closeSDL(SDL_Window*& window);

void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void initSnake(Snake* s);

void drawBorder(SDL_Renderer* renderer, int cellHeight, int cellWidth);
void drawSnake(SDL_Renderer* renderer, Snake* s);
void drawApple(SDL_Renderer* renderer, Apple* a, int cellSize);

int parseKeys(SDL_Event e);

#endif