#pragma once
#ifndef CELL_H
#define CELL_H

class Cell
{
public:
	Cell(int i_, int _j);
	~Cell();

	int i() { return _i; }
	int j() { return _j; }

	Cell* checkNeighbors(vector<Cell*> grid, int rows, int cols);
	void highlight();
	void show();
	bool Visited();
	void toggleWalls(int i, bool b);

private:
	int _i;
	int _j;

	vector<bool> walls{ true, true, true, true }; //TOP, LEFT, BOTTOM, RIGHT

	bool visited = false;
};

#endif