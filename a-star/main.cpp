#include "main.h"
using namespace std;

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


vector<Spot*> removeFromVector(vector<Spot*> openSet, Spot *current)
{
	for (int k = 0; k < openSet.size(); k++)
	{
		if (openSet[k]->i == current->i && openSet[k]->j == current->j)
		{
			openSet.erase(openSet.begin() + k);
			break;
		}
	}
	return openSet;
}

int heuristic(Spot* a, Spot* b)
{
	int d = abs(a->i - b->i) + abs(a->j - b->j);
	return d;
}

bool findSpot(vector<Spot*> set, Spot *s)
{
	for (int k = 0; k < set.size(); k++)
	{
		if (set[k]->i == s->i && set[k]->j == s->j) return true;
	}
	return false;
}

vector<vector<Spot*>> build2DVector(vector<vector<Spot*>> s, int rows, int cols)
{
	for (int i = 0; i < s.size(); i++)
	{
		s[i].resize(rows);
		s[i] = vector<Spot*>(rows);
		for (int j = 0; j < s[i].size(); j++)
		{
			Spot* n = new Spot(i, j);
			int r = (rand() % 100) + 1;
			if (r < 50) n->wall = true;
			s[i][j] = n;
		}
	}
	return s;
}

vector<vector<Spot*>> delete2DVector(vector<vector<Spot*>> s, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			delete s[i][j];
		}
		s[i].clear();
	}
	s.clear();
	return s;
}

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
	bool finished = false;
	int sanityCheck = 0;
	int closestDistance = 0;
	vector<Spot*> tS(rows);
	vector<Spot*> openSet;
	vector<Spot*> closedSet;
	vector<Spot*> path;
	Spot* current = nullptr;
	Spot* start = nullptr;
	Spot* end = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initalize! SDL_ERROR: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("A*", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				return 1;
			}
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	while (true)
	{
		rows = SCREEN_WIDTH / spotWidth;
		cols = SCREEN_HEIGHT / spotHeight;
		sanityCheck = 0;
		finished = false;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		srand(time(0));
		vector<vector<Spot*>> s(cols, tS);
		SDL_Rect *grid = new SDL_Rect[rows*cols];
		// This loop constructs the grid in a 2D array
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				SDL_Rect rectToDraw = { spotWidth * i, spotHeight * j, spotWidth, spotHeight }; // Just some random rect
				grid[i*cols+j] = rectToDraw;
			}
		}
		cout << "Complete." << endl;
		cout << "Assigning positions..." << endl;
		s = build2DVector(s, rows, cols);
		// This loop assigns the spot i/j components
		for (int i = 0; i < s.size(); i++)
		{
			for (int j = 0; j < s[i].size(); j++)
			{
				s[i][j]->i = i;
				s[i][j]->j = j;
			}
		}
		cout << "Complete" << endl;
		cout << "Assigning neighbors..." << endl;
		// This loop assigns spot neighbors

		for (int i = 0; i < s.size(); i++)
		{
			for (int j = 0; j < s[i].size(); j++)
			{
				s[i][j]->addNeighbors(s, cols, rows);
			}
		}
		cout << "Complete" << endl;

		current = nullptr;
		start = s[0][0];
		end = s[cols - 1][rows - 1];
		start->wall = false;
		end->wall = false;
		closestDistance = heuristic(start, end);

		openSet.push_back(start);

		while (true)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) return 0;
			}
			if (sanityCheck == 3 * cols / 2)
			{
				cout << "Sanity Check triggered. Certainty at " << (float)closestDistance / (float)heuristic(start, end) * 1000 << "% for no solution. Breaking." << endl;
				break;
			}
			if (openSet.size() > 0)
			{
				// keep going
				int lowestIndex = 0;
				for (int i = 0; i < openSet.size(); i++)
				{
					if (openSet[i]->f < openSet[lowestIndex]->f)
					{
						lowestIndex = i;
					}
				}
				current = openSet[lowestIndex];

				if (current->i == end->i && current->j == end->j)
				{
					cout << "DONE!" << endl;
					finished = true;
				}


				openSet = removeFromVector(openSet, current);
				closedSet.push_back(current);

				for (int i = 0; i < current->neighbors.size(); i++)
				{
					Spot* neighbor = current->neighbors[i];

					if (!findSpot(closedSet, neighbor) && !neighbor->wall)
					{
						// closedSet does not contain neighbor
						// add walls here also
						int tG = current->g + 1;
						if (findSpot(openSet, neighbor))
						{
							if (tG < neighbor->g) neighbor->g = tG;
						}
						else
						{
							neighbor->g = tG;
							openSet.push_back(neighbor);
						}
						neighbor->h = heuristic(neighbor, end);
						neighbor->f = neighbor->g + neighbor->h;
						neighbor->previous = current;
					}
				}
			}
			else
			{
				cout << "NO SOLUTION!" << endl;
				finished = true;
			}

			// This loop draws the grid black on white

			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
			for (int i = 0; i < s.size(); i++)
			{
				for (int j = 0; j < s[i].size(); j++)
				{
					if (s[i][j]->wall)
						SDL_RenderFillRect(renderer, &grid[i * cols + j]);
				}
			}

			// This loop draw the closed set red on white
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
			for (int k = 0; k < closedSet.size(); k++)
			{
				int i = closedSet[k]->i;
				int j = closedSet[k]->j;
				SDL_RenderFillRect(renderer, &grid[i * cols + j]);
			}
			// This loop draws the open set green on white
			SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0xFF);
			for (int k = 0; k < openSet.size(); k++)
			{
				int i = openSet[k]->i;
				int j = openSet[k]->j;
				SDL_RenderFillRect(renderer, &grid[i * cols + j]);
			}

			if (!finished)
			{
				if (heuristic(current, end) > closestDistance) sanityCheck += 1;
				else
				{
					sanityCheck = 0;
					closestDistance = heuristic(current, end);
				}
				path.clear();
				path.push_back(current);
				while (current->previous != nullptr)
				{
					path.push_back(current->previous);
					current = current->previous;
				}
			}

			// This loop draws the path blue on white
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0xFF, 0xFF);
			for (int k = 0; k < path.size(); k++)
			{
				int i = path[k]->i;
				int j = path[k]->j;
				SDL_RenderFillRect(renderer, &grid[i * cols + j]);
			}

			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			for (int i = 0; i < cols; i++)
			{
				for (int j = 0; j < rows; j++)
				{
					SDL_RenderDrawRect(renderer, &grid[i * cols + j]);
				}
			}

			SDL_UpdateWindowSurface(window);
			SDL_RenderPresent(renderer); //Update renderer

			if (finished) break;
			SDL_Delay(solveSpeed);
			//SDL_Delay(500);
		}
		s = delete2DVector(s, rows, cols);
		while (!openSet.empty()) openSet.erase(openSet.end() - 1);
		while (!closedSet.empty()) closedSet.erase(closedSet.end() - 1);
		while (!path.empty()) path.erase(path.end() - 1);

		delete[] grid;

		lua_State* L = luaL_newstate();
		luaL_openlibs(L);

		if (CheckLua(L, luaL_dofile(L, "stuff.lua")))
		{
			LoadSettings(L, SCREEN_WIDTH, SCREEN_HEIGHT, spotWidth, spotHeight, solveSpeed);
		}
		lua_close(L);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}