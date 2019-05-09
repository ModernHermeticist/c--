#pragma once
class Apple
{
public:
	Apple(int _xPos, int _yPos)
	{
		xPos = _xPos;
		yPos = _yPos;
	};
	~Apple() {};
	int xPos;
	int yPos;
};



class Cell
{
public:
	Cell(int _xPos, int _yPos);
	~Cell();
	int xPos;
	int yPos;
	int oldXPos;
	int oldYPos;
	Cell* next = nullptr;

};



class Snake
{
public:
	enum Direction{Up, Right, Down, Left};

	int lastDirection = Right;

	Snake(int _cellSize);
	~Snake();
	void AddCellToBody();
	int GetBodySize() { return body.size(); }
	int GetCellSize() { return cellSize; }
	Cell* GetCellFromBody(int index) { return body[index];}
	bool MoveSnake();

private:
	std::vector<Cell*> body;
	int cellSize;
};

