#include "main.h"
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int spotWidth = 25;
const int spotHeight = 25;


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

int main(int argc, char* args[])
{
	while (true)
	{
		srand(time(0));
		const int rows = SCREEN_WIDTH / spotWidth;
		const int cols = SCREEN_HEIGHT / spotHeight;
		bool finished = false;
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		SDL_Surface* screenSurface = NULL;
		vector<Spot> tS(rows);
		vector<vector<Spot>> s(cols, tS);
		for (int i = 0; i < rows; i++)
		{
			s[i].resize(cols);
			s[i] = vector<Spot>(cols);
			for (int j = 0; j < cols; j++)
			{
				Spot* n = new Spot(i, j);
				int r = (rand() % 100) + 1;
				if (r < 40) n->wall = true;
				s[i][j] = *n;
			}
		}
		cout << "Spots generated" << endl;
		SDL_Rect grid[rows][cols];

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
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);


				cout << "Constructing 2D array..." << endl;
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
				// This loop assigns the spot i/j components
				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						s[i][j].i = i;
						s[i][j].j = j;
					}
				}
				cout << "Complete" << endl;
				cout << "Assigning neighbors..." << endl;
				// This loop assigns spot neighbors

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < cols; j++)
					{
						s[i][j].addNeighbors(s, cols, rows);
					}
				}
				cout << "Complete" << endl;

				vector<Spot*> openSet;
				vector<Spot*> closedSet;
				vector<Spot*> path;
				Spot* current;
				Spot* start = &s[0][0];
				Spot* end = &s[cols - 1][rows - 1];
				start->wall = false;
				end->wall = false;

				openSet.push_back(start);

				while (true)
				{
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


					SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_RenderClear(renderer);
					// This loop draws the grid black on white
					SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
					for (int i = 0; i < rows; i++)
					{
						for (int j = 0; j < cols; j++)
						{
							SDL_RenderDrawRect(renderer, &grid[i][j]);
						}
					}

					SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0x0);
					for (int i = 0; i < rows; i++)
					{
						for (int j = 0; j < cols; j++)
						{
							if (s[i][j].wall)
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

					SDL_UpdateWindowSurface(window);
					SDL_RenderPresent(renderer); //Update renderer

					if (finished) break;
					SDL_Delay(100);
					//SDL_Delay(500);
				}
				SDL_Delay(1000);
				//system("PAUSE");
			}
		}

		SDL_DestroyWindow(window);

		SDL_Quit();

	}

	return 0;
}