#include "main.h"


int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Event e;
	std::vector<Cell*> cells;

	int oldMouseX = -1;
	int oldMouseY = -1;
	int mouseX = -1;
	int mouseY = -1;

	bool finished = false;
	bool toggleHighlightedCell = false;

	GenerateGridofCells(cells);


	if (!initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return -1;


	// MAIN LOOP
	while (!finished)
	{
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		DrawGridofCells(renderer, cells);

		if (toggleHighlightedCell || mouseX != oldMouseX && mouseY != oldMouseY)
		{
			Cell* c = nullptr;
			for (int i = 0; i < cellNum; i++)
			{
				for (int j = 0; j < cellNum; j++)
				{
					c = cells[i + j * cellNum];
					if (toggleHighlightedCell)
					{
						c->ToggleSelected();
						toggleHighlightedCell = false;
					}
					else
					{
						if (c->compareXandY(mouseX, mouseY)) c->Highlight();
						else if (!c->Selected()) c->ResetColor();
					}
				}
			}
			oldMouseX = mouseX;
			oldMouseY = mouseY;
		}

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&e) != 0)
		{
			int kp = parseKeys(e);
			if (kp == Quit)
			{
				finished = true;
				break;
			}


			if (e.type == SDL_MOUSEMOTION)
			{
				mouseX = -1;
				mouseY = -1;
				SDL_GetMouseState(&mouseX, &mouseY);
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				toggleHighlightedCell = true;
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
	//vc.resize(cellNum * cellNum);
	for (int i = 0; i < cellNum; i++)
	{
		for (int j = 0; j < cellNum; j++)
		{
			Cell* c = new Cell(i * cellSize, j * cellSize);
			vc.push_back(c);
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
