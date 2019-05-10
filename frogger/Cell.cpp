#include "main.h"



Cell::Cell(int _xPos, int _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
}


Cell::~Cell()
{

}

void Cell::Draw(SDL_Renderer* renderer, bool fill, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	drawGenericRect(renderer, xPos, yPos, CELL_SIZE, CELL_SIZE, r, g, b, a, fill);
}
