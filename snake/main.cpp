#include "main.h"

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	int cellHeight = SCREEN_HEIGHT / cells;
	int cellWidth = cellHeight;
	int cellSize = cellWidth;
	bool appleExists = false;

	Snake* s = new Snake(cellSize);
	Apple* a = new Apple(rand() % ((cells - 1) + 1) * cellSize, rand() % ((cells - 1) + 1) * cellSize);
	std::cout << "apple xPos = " << a->xPos << std::endl;
	std::cout << "apple yPos = " << a->yPos << std::endl;
	Cell* front = s->GetCellFromBody(0);
	bool finished = false;

	if (!initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return -1;

	initSnake(s);

	// MAIN LOOP
	while (!finished)
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		drawBorder(renderer, cellHeight, cellWidth);

		drawSnake(renderer, s);

		drawApple(renderer, a, cellSize);

		SDL_RenderPresent(renderer);

		if(!s->MoveSnake()) break;
		if (front->xPos == a->xPos && front->yPos == a->yPos)
		{
			int newX = rand() % (cells - 2) + 1;
			int newY = rand() % (cells - 2) + 1;
			newX *= cellSize;
			newY *= cellSize;
			delete a;
			s->AddCellToBody();
			a = new Apple(newX, newY);
			std::cout << "apple xPos = " << a->xPos << std::endl;
			std::cout << "apple yPos = " << a->yPos << std::endl;
		}

		SDL_Delay(75);
		while (SDL_PollEvent(&e) != 0)
		{
			int kp = parseKeys(e);
			if (kp == quit)
			{
				finished = true;
				break;
			}
			else if (kp == GoLeft) s->lastDirection = s->Left;
			else if (kp == GoRight) s->lastDirection = s->Right;
			else if (kp == GoUp) s->lastDirection = s->Up;
			else if (kp == GoDown) s->lastDirection = s->Down;
		}
	}

	delete s;

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

void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_Rect rect{ xPos, yPos, width, height };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);
}

void drawBorder(SDL_Renderer* renderer, int cellHeight, int cellWidth)
{
	drawGenericRect(renderer, 0, 0, SCREEN_WIDTH, cellHeight, 0x0, 0xFF, 0xA0, 0xFF);
	drawGenericRect(renderer, 0, SCREEN_HEIGHT - cellHeight, SCREEN_WIDTH, cellHeight, 0x0, 0xFF, 0xA0, 0xFF);
	drawGenericRect(renderer, 0, 0, cellWidth, SCREEN_HEIGHT, 0x0, 0xFF, 0xA0, 0xFF);
	drawGenericRect(renderer, SCREEN_WIDTH - cellWidth, 0, cellWidth, SCREEN_HEIGHT, 0x0, 0xFF, 0xA0, 0xFF);
}

void drawSnake(SDL_Renderer* renderer, Snake* s)
{
	for (int k = 0; k < s->GetBodySize(); k++)
	{
		Cell* c = s->GetCellFromBody(k);
		drawGenericRect(renderer, c->xPos, c->yPos, s->GetCellSize(), s->GetCellSize(), 0x0, 0x0, 0xFF, 0xFF);
	}
}

void drawApple(SDL_Renderer* renderer, Apple* a, int cellSize)
{
	drawGenericRect(renderer, a->xPos, a->yPos, cellSize, cellSize, 0xFF, 0x0, 0xA0, 0xFF);
}

void initSnake(Snake* s)
{
	for (int i = 0; i < 4; i++)
	{
		s->AddCellToBody();
	}
}

int parseKeys(SDL_Event e)
{
	if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
	{
		return quit;
	}

	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
	{
		return GoLeft;
	}

	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
	{
		return GoRight;
	}

	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
	{
		return GoUp;
	}

	else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
	{
		return GoDown;
	}
}