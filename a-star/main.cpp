#include "main.h"
using namespace std;

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

const int spotWidth = 5;
const int spotHeight = 5;


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
	for (int i = 0; i < rows; i++)
	{
		s[i].resize(cols);
		s[i] = vector<Spot*>(cols);
		for (int j = 0; j < cols; j++)
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
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Event e;
	const int rows = SCREEN_WIDTH / spotWidth;
	const int cols = SCREEN_HEIGHT / spotHeight;
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
		sanityCheck = 0;
		finished = false;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		srand(time(0));
		vector<vector<Spot*>> s(cols, tS);
		SDL_Rect grid[rows][cols];
		// This loop constructs the grid in a 2D array
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				SDL_Rect rectToDraw = { spotWidth * i, spotHeight * j, spotWidth, spotHeight }; // Just some random rect
				grid[i][j] = rectToDraw;
			}
		}
		cout << "Complete." << endl;
		cout << "Assigning positions..." << endl;
		s = build2DVector(s, rows, cols);
		start = s[0][0];
		end = s[cols - 1][rows - 1];
		start->wall = false;
		end->wall = false;
		closestDistance = heuristic(start, end);
		// This loop assigns the spot i/j components
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				s[i][j]->i = i;
				s[i][j]->j = j;
			}
		}
		cout << "Complete" << endl;
		cout << "Assigning neighbors..." << endl;
		// This loop assigns spot neighbors

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				s[i][j]->addNeighbors(s, cols, rows);
			}
		}
		cout << "Complete" << endl;

		current = nullptr;
		start = s[0][0];
		end = s[cols - 1][rows - 1];

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
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					if (s[i][j]->wall)
						SDL_RenderFillRect(renderer, &grid[i][j]);
				}
			}

			// This loop draw the closed set red on white
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
			for (int k = 0; k < closedSet.size(); k++)
			{
				int i = closedSet[k]->i;
				int j = closedSet[k]->j;
				SDL_RenderFillRect(renderer, &grid[i][j]);
			}
			// This loop draws the open set green on white
			SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 0xFF);
			for (int k = 0; k < openSet.size(); k++)
			{
				int i = openSet[k]->i;
				int j = openSet[k]->j;
				SDL_RenderFillRect(renderer, &grid[i][j]);
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
				SDL_RenderFillRect(renderer, &grid[i][j]);
			}

			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					SDL_RenderDrawRect(renderer, &grid[i][j]);
				}
			}

			SDL_UpdateWindowSurface(window);
			SDL_RenderPresent(renderer); //Update renderer

			if (finished) break;
			SDL_Delay(1000/60);
			//SDL_Delay(500);
		}
		s = delete2DVector(s, rows, cols);
		while (!openSet.empty()) openSet.erase(openSet.end() - 1);
		while (!closedSet.empty()) closedSet.erase(closedSet.end() - 1);
		while (!path.empty()) path.erase(path.end() - 1);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}