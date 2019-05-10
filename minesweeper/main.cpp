#include "main.h"


int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	std::vector<Cell*> cells;

	int oldMouseX = 0;
	int oldMouseY = 0;

	bool finished = false;

	GenerateGridofCells(cells);


	if (!initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return -1;


	// MAIN LOOP
	while (!finished)
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		DrawGridofCells(renderer, cells);

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				int x = -1;
				int y = -1;
				SDL_GetMouseState(&x, &y);
				if (x != oldMouseX && y != oldMouseY)
				{
					Cell* c = nullptr;
					for (int i = 0; i < cellNum; i++)
					{
						for (int j = 0; j < cellNum; j++)
						{
							c = cells[i + j * cellNum];
							if (c->compareXandY(x, y)) c->Highlight();
						}
					}
				}
				std::cout << "Mouse x: " << x << std::endl;
				std::cout << "Mouse y: " << y << std::endl;
				std::cout << std::endl;
				oldMouseX = x;
				oldMouseY = y;
			}
		}


		SDL_Delay(1);
		while (SDL_PollEvent(&e) != 0)
		{
			int kp = parseKeys(e);
			if (kp == Quit)
			{
				finished = true;
				break;
			}
		}
	}

	for (int i = 0; i < cells.size(); i++) delete cells[i];
	cells.resize(0);

	closeSDL(window);


	return 0;
}



int parseKeys(SDL_Event e)
{
	if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
	{
		return Quit;
	}
}


void GenerateGridofCells(std::vector<Cell*>& vc)
{
	vc.resize(cellNum * cellNum);
	for (int i = 0; i < cellNum; i++)
	{
		for (int j = 0; j < cellNum; j++)
		{
			Cell* c = new Cell(i * cellSize, j * cellSize);
			vc[i + j * cellNum] = c;
		}
	}
}

void DrawGridofCells(SDL_Renderer* r, std::vector<Cell*> vc)
{
	for (int i = 0; i < cellNum; i++)
	{
		for (int j = 0; j < cellNum; j++)
		{
			vc[i + j * cellNum]->Draw(r, true);
			vc[i + j * cellNum]->Draw(r, false);
		}
	}
}
