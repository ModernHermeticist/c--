#include "main.h"

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initalize! SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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