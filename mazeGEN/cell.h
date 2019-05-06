#pragma once
#ifndef CELL_H
#define CELL_H

class Cell
{
public:
	Cell(int i_, int _j);
	~Cell();

	int i() { return _i; }
	void i(int num) { _i = num; }
	int j() { return _j; }
	void j(int num) { _j = num; }
	int f() { return _f; }
	void f(int num) { _f = num; }
	int g() { return _g; }
	void g(int num) { _g = num; }
	int h() { return _h; }
	void h(int num) { _h = num; }
	Cell* previous() { return _previous; }
	void previous(Cell* tC) { _previous = tC; }

	Cell* checkNeighbors(std::vector<Cell*> grid, int rows, int cols);
	void addNeighbors(std::vector<Cell*> grid, int rows, int cols);
	void highlight(SDL_Renderer* renderer, int w, Uint8 r, Uint8 g, Uint8 b);
	void show(SDL_Renderer* renderer, int w, bool aStar);
	bool Visited();
	void Start();
	void End();
	void SetVisited(bool v);
	void toggleWalls(int i, bool b);

	std::vector<Cell*> neighbors;

	enum Wall { top, right, bottom, left };

private:
	int _i;
	int _j;
	int _f = 0;
	int _g = 0;
	int _h = 0;

	Cell* _previous = nullptr;

	std::vector<bool> walls{ true, true, true, true }; //TOP, LEFT, BOTTOM, RIGHT
	bool visited = false;
	bool start = false;
	bool end = false;
};

#endif