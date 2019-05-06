#include "main.h"


int main(int argc, char* args[])
{
	int SCREEN_WIDTH = 800;
	int SCREEN_HEIGHT = 800;

	int spotWidth = 15;
	int spotHeight = spotWidth;

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
	int rows = (SCREEN_WIDTH) / spotWidth;
	int cols = (SCREEN_HEIGHT) / spotHeight;
	int w = spotWidth;

	vector<Cell*> grid = generateCellGrid(rows, cols);
	vector<Cell*> stack;
	Cell* current = grid[0];
	current->Start();
	grid.back()->End();

	vector<Cell*> tS(rows);
	vector<Cell*> openSet;
	vector<Cell*> closedSet;
	vector<Cell*> path;
	Cell* start = nullptr;
	Cell* end = nullptr;

	bool finished = false;

	initSDL(window, renderer, screenSurface, SCREEN_WIDTH+1, SCREEN_HEIGHT+1);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	clock_t beginT = clock();
	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) return 0;
		}
		if (!draw(window, renderer, grid, stack, current, w, rows, cols)) break;
		//SDL_Delay(1);
	}
	clock_t endT = clock();
	cout << "Runtime: " << endT - beginT << endl;
	for (int k = 0; k < grid.size(); k++)
	{
		grid[k]->addNeighbors(grid, rows, cols);
	}

	current = nullptr;
	start = grid[0];
	end = grid.back();

	openSet.push_back(start);

	/*
	while (true)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) return 0;
		}

		if (openSet.size() > 0)
		{
			int lowestIndex = 0;
			for (int i = 0; i < openSet.size(); i++)
			{
				if (openSet[i]->f() < openSet[lowestIndex]->f())
				{
					lowestIndex = i;
				}
			}
			current = openSet[lowestIndex];

			if (current->i() == end->i() && current->j() == end->j())
			{
				cout << "DONE!" << endl;
				finished = true;
			}

			openSet = removeFromVector(openSet, current);
			closedSet.push_back(current);

			for (int i = 0; i < current->neighbors.size(); i++)
			{
				Cell* neighbor = current->neighbors[i];

				if (!findCell(closedSet, neighbor))
				{
					// closedSet does not contain neighbor
					// add walls here also
					int tG = current->g() + 1;
					if (findCell(openSet, neighbor))
					{
						if (tG < neighbor->g()) neighbor->g(tG);
					}
					else
					{
						neighbor->g(tG);
						openSet.push_back(neighbor);
					}
					neighbor->h(heuristic(neighbor, end));
					neighbor->f(neighbor->g() + neighbor->h());
					neighbor->previous(current);
				}
			}
		}
		else
		{
			cout << "NO SOLUTION!" << endl;
			finished = true;
		}
	}*/
	//while (!openSet.empty()) openSet.erase(openSet.end() - 1);
	//while (!closedSet.empty()) closedSet.erase(closedSet.end() - 1);
	//while (!path.empty()) path.erase(path.end() - 1);

	system("PAUSE");

	for (int i = 0; i < grid.size(); i++)
		delete grid[i];
	grid.resize(0);

	closeSDL(window);


	return 0;
}


bool draw(SDL_Window* window, SDL_Renderer* renderer, vector<Cell*> grid, vector<Cell*> &stack, Cell* &current, int w, int rows, int cols)
{
	for (int i = 0; i < grid.size(); i++)
		grid[i]->show(renderer, w, false);
	current->SetVisited(true);
	current->highlight(renderer, w, 0x00, 0x00, 0xFF);

	Cell* next = current->checkNeighbors(grid, rows, cols);
	if (next)
	{
		next->SetVisited(true);
		stack.push_back(current);
		removeWalls(current, next);
		current = next;
	}
	else if (stack.size() > 0)
	{
		current = stack.back();
		stack.pop_back();
	}
	else
	{
		//for (int i = 0; i < grid.size(); i++)
			//grid[i]->show(renderer, w, false);
		//SDL_RenderPresent(renderer); //Update renderer
		return false;
	}
	SDL_RenderPresent(renderer);
	return true;
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

bool initSDL(SDL_Window* window, SDL_Renderer* &renderer, SDL_Surface* screenSurface, int SCREEN_WIDTH, int SCREEN_HEIGHT)
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
	printf("SDL Initialized!\n");
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

int heuristic(Cell* a, Cell* b)
{
	int d = abs(a->i() - b->i()) + abs(a->j() - b->j());
	return d;
}

vector<Cell*> removeFromVector(vector<Cell*> openSet, Cell* current)
{
	for (int k = 0; k < openSet.size(); k++)
	{
		if (openSet[k]->i() == current->i() && openSet[k]->j() == current->j())
		{
			openSet.erase(openSet.begin() + k);
			break;
		}
	}
	return openSet;
}

bool findCell(vector<Cell*> set, Cell* s)
{
	for (int k = 0; k < set.size(); k++)
	{
		if (set[k]->i() == s->i() && set[k]->j() == s->j()) return true;
	}
	return false;
}