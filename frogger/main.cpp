#include "main.h"

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	int laneHeight = SCREEN_HEIGHT / lanes;

	std::vector<Cell*> cells;
	
	for (int i = 0; i < lanes; i++)
	{
		for (int j = 0; j < lanes; j++)
		{
			Cell* c = new Cell(CELL_SIZE * i, CELL_SIZE * j);
			cells.push_back(c);
		}
	}

	


	bool finished = false;

	if (!initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return -1;

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	drawBackground(renderer, laneHeight);
	for (int i = 0; i < lanes; i++)
	{
		for (int j = 0; j < lanes; j++)
		{
			cells[i + j * lanes]->Draw(renderer, true, 0xFF, 0x0, 0x0, 0xFF);
			cells[i + j * lanes]->Draw(renderer, false, 0x0, 0x0, 0x0, 0xFF);
		}
	}
	SDL_RenderPresent(renderer);
	// MAIN LOOP
	while (!finished)
	{
		if (parseInput() == 0) finished = true;
	}

	for (int i = 0; i < cells.size(); i++) delete cells[i];
	cells.resize(0);

	closeSDL(window);
	return 0;
}



bool initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initalize! SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow("Frogger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

void closeSDL(SDL_Window* &window)
{
	SDL_DestroyWindow(window);

	SDL_Quit();
}

void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool fill)
{
	SDL_Rect rect{ xPos, yPos, width, height };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	if (fill) SDL_RenderFillRect(renderer, &rect);
	else SDL_RenderDrawRect(renderer, &rect);
}

void drawBackground(SDL_Renderer* renderer, int laneHeight)
{
	drawGenericRect(renderer, 0, 0, SCREEN_WIDTH, laneHeight / 4, 0x0, 0xFF, 0xA0, 0xFF, true);
	drawGenericRect(renderer, 0, SCREEN_HEIGHT - laneHeight, SCREEN_WIDTH, laneHeight, 0x0, 0xFF, 0xA0, 0xFF, true);
}

int parseInput()
{
	SDL_Event e;


	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		{
			return Exit;
		}
	}
	return -1;
}