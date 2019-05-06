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
#include <math.h>
#include <ctime>
#include "cell.h"

using namespace std;


#pragma comment(lib, "../lua/liblua53.a")
#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")


bool CheckLua(lua_State* L, int r);
void LoadSettings(lua_State* L, int& SCREEN_WIDTH, int& SCREEN_HEIGHT, int& spotWidth, int& spotHeight, int& solveSpeed);
bool initSDL(SDL_Window* window, SDL_Renderer* &renderer, SDL_Surface* screenSurface, int SCREEN_WIDTH, int SCREEN_HEIGHT);
void closeSDL(SDL_Window* window);
int index(int i, int j, int rows, int cols);
vector<Cell*> generateCellGrid(int rows, int cols);
void removeWalls(Cell* a, Cell* b);
bool draw(SDL_Window* window, SDL_Renderer* renderer, vector<Cell*> grid, vector<Cell*>& stack, Cell* &current, int w, int rows, int cols);
int heuristic(Cell* a, Cell* b);
bool findCell(vector<Cell*> set, Cell* s);
vector<Cell*> removeFromVector(vector<Cell*> openSet, Cell* current);

#endif