#include "main.h"

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	int laneWidth = SCREEN_WIDTH / lanes;

	std::vector<int> randomNumberSet;


	bool finished = false;
	int t = 0;
	if (!initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return -1;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	// MAIN LOOP
	while (!finished)
	{
		for (int k = 0; k < lanes; k++) randomNumberSet.push_back(rand() % SCREEN_HEIGHT + 1);
		if (!bubbleSort(renderer, randomNumberSet, laneWidth)) break;
		randomNumberSet.clear();
		randomNumberSet.resize(0);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				finished = true;
				break;
			}
		}
	}
	closeSDL(window);
	return 0;
}



bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initalize! SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Failed to create window! SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Failed to create renderer! SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "SDL Initialized!" << std::endl;
	return true;
}

void closeSDL(SDL_Window*& window)
{
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect rect{ xPos, yPos, width, height };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderDrawRect(renderer, &rect);
}

bool bubbleSort(SDL_Renderer* renderer, std::vector<int> &v, int laneWidth)
{
	SDL_Event e;
	int t = 0;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v.size() - i - 1; j++)
		{
			SDL_RenderClear(renderer);
			for (int k = 0; k < v.size(); k++)
			{
				drawGenericRect(renderer, laneWidth * k, SCREEN_HEIGHT, laneWidth, v[k] - SCREEN_HEIGHT, 0x0, 0xFF, 0xA0, 0xFF);
				if (k == j)
					drawGenericRect(renderer, laneWidth * k, SCREEN_HEIGHT, laneWidth, v[k] - SCREEN_HEIGHT, 0xFF, 0x0, 0x0, 0xFF);
				if (k == j + 1)
					drawGenericRect(renderer, laneWidth * k, SCREEN_HEIGHT, laneWidth, v[k] - SCREEN_HEIGHT, 0x0, 0x0, 0xFF, 0xFF);
			}

			if (v[j] < v[j + 1])
			{
				t = v[j];
				v[j] = v[j + 1];
				v[j + 1] = t;
			}

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				{
					return false;
				}
			}
			SDL_RenderPresent(renderer);
			SDL_Delay(solveSpeed);
		}
	}
	return true;
}