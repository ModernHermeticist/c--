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
	Cell* c = new Cell(SCREEN_WIDTH / 2 - cellSize / 2, SCREEN_HEIGHT / 2 - cellSize / 2);
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
	c->next = backCell;
	body.push_back(c);
}

bool Snake::MoveSnake()
{
	int x = 0;
	int y = 0;

	Cell* current = nullptr;
	if (lastDirection == Up) y = -1;
	else if (lastDirection == Down) y = 1;
	else if (lastDirection == Left) x = -1;
	else if (lastDirection == Right) x = 1;

	body.front()->oldXPos = body.front()->xPos;
	body.front()->oldYPos = body.front()->yPos;
	body.front()->xPos += cellSize * x;
	body.front()->yPos += cellSize * y;

	if (body.front()->xPos > SCREEN_WIDTH - cellSize || body.front()->xPos < cellSize ||
		body.front()->yPos > SCREEN_HEIGHT - cellSize || body.front()->yPos < cellSize)
		return false;

	for (int k = 1; k < body.size(); k++)
	{
		current = body[k];
		current->oldXPos = current->xPos;
		current->oldYPos = current->yPos;
		current->xPos = current->next->oldXPos;
		current->yPos = current->next->oldYPos;
	}
	return true;
}