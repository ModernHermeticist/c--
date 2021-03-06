#include "main.h"



Cell::Cell(int _xPos, int _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
	col.r = 169;
	col.g = 169;
	col.b = 169;
	selected = false;
}


Cell::~Cell()
{
}

void Cell::Draw(SDL_Renderer* renderer, bool fill)
{
	drawGenericRect(renderer, xPos, yPos, cellSize, cellSize, col.r, col.g, col.b, 0xFF, true);
	drawGenericRect(renderer, xPos, yPos, cellSize, cellSize, 0, 0, 0, 0xFF, false);
}

void Cell::Highlight()
{
	col.r = 255;
	col.g = 0;
	col.b = 0;
}

bool Cell::compareXandY(int x, int y)
{
	if (xPos <= x && x <= xPos + cellSize && yPos <= y && y <= yPos + cellSize) return true;
	else return false;
}

void Cell::ResetColor()
{
	col.r = 169;
	col.g = 169;
	col.b = 169;
}

void Cell::ToggleSelected()
{
	if (selected) selected = false;
	else selected = true;
}

void Cell::SetNeighbors(std::vector<Cell*> grid)
{

}
