#pragma once
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
	enum Direction{up, right, down, left};

	int lastDirection = right;

	Snake(int _cellSize);
	~Snake();
	void AddCellToBody();
	int GetBodySize() { return body.size(); }
	int GetCellSize() { return cellSize; }
	Cell* GetCellFromBody(int index) { return body[index];}
	void MoveSnake();

private:
	std::vector<Cell*> body;
	int cellSize;
};

