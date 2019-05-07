#include "main.h"



Cell::Cell(int _xPos, int _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
	oldXPos = xPos;
	oldYPos = yPos;
}


Cell::~Cell()
{

}

//###################################//
//###################################//
//###################################//


Snake::Snake(int _cellSize)
{
	cellSize = _cellSize;
	Cell* c = new Cell(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	c->next = body.back();
	body.push_back(c);
}


Snake::~Snake()
{
	while (body.size() > 0)
	{
		delete body.back();
		body.pop_back();
	}
}

void Snake::AddCellToBody()
{
	Cell* backCell = body.back();
	Cell* c = new Cell(backCell->xPos - cellSize, backCell->yPos);
	body.push_back(c);
}

void Snake::MoveSnake()
{
	int x = 0;
	int y = 0;

	Cell* current = nullptr;
	if (lastDirection == up) y = -1;
	else if (lastDirection == down) y = 1;
	else if (lastDirection == left) x = -1;
	else if (lastDirection == right) x = 1;

	body.front()->xPos += cellSize * x;
	body.front()->yPos += cellSize * y;

	current = body.back();

	while (current != body.front())
	{
		current->xPos = current->next->xPos;
		current->yPos = current->next->yPos;
	}
}