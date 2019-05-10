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

#include "sdl_handler.h"
#include "gui.h"
#include "Cell.h"


#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int cellNum = 25;
const int cellSize = SCREEN_HEIGHT / cellNum;

enum KeyHandler{Quit};


int parseKeys(SDL_Event e);
void GenerateGridofCells(std::vector<Cell*>& cells);
void DrawGridofCells(SDL_Renderer* r, std::vector<Cell*> vc);

#endif