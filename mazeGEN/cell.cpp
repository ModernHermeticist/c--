#include "main.h"

Cell::Cell(int i_, int j_)
{
	_i = i_;
	_j = j_;
}

Cell::~Cell()
{}

Cell* Cell::checkNeighbors(vector<Cell*> grid, int rows, int cols)
{
	vector<Cell*> neighbors;
	Cell* neighbor = grid[index(_i, _j - 1, rows, cols)];
	if (neighbor && !neighbor->Visited())
		neighbors.push_back(neighbor);

	neighbor = grid[index(_i + 1, _j, rows, cols)];

	if (neighbor && !neighbor->Visited())
		neighbors.push_back(neighbor);

	neighbor = grid[index(_i, _j + 1, rows, cols)];

	if (neighbor && !neighbor->Visited())
		neighbors.push_back(neighbor);

	neighbor = grid[index(_i - 1, _j, rows, cols)];

	if (neighbor && !neighbor->Visited())
		neighbors.push_back(neighbor);

	if (neighbors.size() > 0)
	{
		int r = floor(rand() % neighbors.size());
		return neighbors[r];
	}
	return NULL;
}


bool Cell::Visited()
{
	if (visited) return true;
	else return false;
}

void Cell::toggleWalls(int i, bool b)
{
	walls[i] = b;
}