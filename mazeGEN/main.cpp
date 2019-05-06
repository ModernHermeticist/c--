#include "main.h"


int main(int argc, char* args[])
{
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 800;

	int spotWidth = 25;
	int spotHeight = 25;

	int solveSpeed = 0;

	lua_State* L = luaL_newstate();
	//luaL_openlibs(L);

	if (CheckLua(L, luaL_dofile(L, "stuff.lua")))
	{
		LoadSettings(L, SCREEN_WIDTH, SCREEN_HEIGHT, spotWidth, spotHeight, solveSpeed);
	}
	lua_close(L);

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Event e;
	int rows = SCREEN_WIDTH / spotWidth;
	int cols = SCREEN_HEIGHT / spotHeight;

	vector<Cell*> grid = generateCellGrid(rows, cols);
	Cell* current = grid[0];

	initSDL(window, renderer, screenSurface, SCREEN_WIDTH, SCREEN_HEIGHT);

	system("PAUSE");

	closeSDL(window);


	return 0;
}



bool CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		string errormsg = lua_tostring(L, -1);
		cout << errormsg << endl;
		return false;
	}
	return true;
}

void LoadSettings(lua_State * L, int& SCREEN_WIDTH, int& SCREEN_HEIGHT, int& spotWidth, int& spotHeight, int& solveSpeed)
{
	lua_getglobal(L, "SCREEN_WIDTH");
	if (lua_isnumber(L, -1))
		SCREEN_WIDTH = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "SCREEN_HEIGHT");
	if (lua_isnumber(L, -1))
		SCREEN_HEIGHT = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "spotWidth");
	if (lua_isnumber(L, -1))
		spotWidth = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "spotHeight");
	if (lua_isnumber(L, -1))
		spotHeight = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "solveSpeed");
	if (lua_isnumber(L, -1))
		solveSpeed = (int)lua_tonumber(L, -1);
}

bool initSDL(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* screenSurface, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initalize! SDL_ERROR: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		window = SDL_CreateWindow("A*", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return false;
			}
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return true;
}

void closeSDL(SDL_Window* window)
{
	SDL_DestroyWindow(window);

	SDL_Quit();
}

int index(int i, int j, int rows, int cols)
{
	if (i < 0 || j < 0 || i > cols - 1 || j > rows - 1)
		return -1;
	else
		return i + j * cols;
}

vector<Cell*> generateCellGrid(int rows, int cols)
{
	vector<Cell*> grid;
	for (int j = 0; j < rows; j++)
	{
		for (int i = 0; i < cols; i++)
		{
			Cell* cell = new Cell(i, j);
			grid.push_back(cell);
		}
	}
	return grid;
}

void removeWalls(Cell* a, Cell* b)
{
	int x = a->i() - b->i();
	int y = a->j() - b->j();

	if (x == 1)
	{
		a->toggleWalls(3, false);
		b->toggleWalls(1, false);
	}
	else if (x == -1)
	{
		a->toggleWalls(1, false);
		b->toggleWalls(3, false);
	}

	else if (y == 1)
	{
		a->toggleWalls(0, false);
		b->toggleWalls(2, false);
	}
	else if (y == -1)
	{
		a->toggleWalls(2, false);
		b->toggleWalls(0, false);
	}
}