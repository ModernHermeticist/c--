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
	Cell* neighbor;
	int tI = index(_i, _j - 1, rows, cols);
	if (tI > -1)
	{
		neighbor = grid[tI];
		if (!neighbor->Visited())
			neighbors.push_back(neighbor);
	}

	tI = index(_i + 1, _j, rows, cols);
	if (tI > -1)
	{
		neighbor = grid[tI];
		if (!neighbor->Visited())
			neighbors.push_back(neighbor);
	}

	tI = index(_i, _j + 1, rows, cols);
	if (tI > -1)
	{
		neighbor = grid[tI];
		if (!neighbor->Visited())
			neighbors.push_back(neighbor);
	}

	tI = index(_i - 1, _j, rows, cols);
	if (tI > -1)
	{
		neighbor = grid[tI];
		if (!neighbor->Visited())
			neighbors.push_back(neighbor);
	}

	if (neighbors.size() > 0)
	{
		int r = floor(rand() % neighbors.size());
		return neighbors[r];
	}
	return NULL;
}

void Cell::addNeighbors(vector<Cell*> grid, int rows, int cols)
{
	Cell* tN = nullptr;
	if (_i < cols - 1 && !walls[right])
	{
		tN = grid[(_i + 1) + _j * cols];
		neighbors.push_back(tN);
	}
	if (_i > 0 && !walls[left])
	{
		tN = grid[(_i - 1) + _j * cols];
		neighbors.push_back(tN);
	}
	if (_j < rows - 1 && !walls[bottom])
	{
		tN = grid[_i + (_j + 1) * cols];
		neighbors.push_back(tN);
	}
	if (_j > 0 && !walls[top])
	{
		tN = grid[_i + (_j - 1) * cols];
		neighbors.push_back(tN);
	}
}


void Cell::show(SDL_Renderer* renderer, int w, bool aStar)
{
	int x = _i * w;
	int y = _j * w;
	SDL_Rect t = { x , y, w, w };

	if (aStar)
	{
		SDL_RenderFillRect(renderer, &t);
		return;
	}

	if (visited)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderFillRect(renderer, &t);
	}
	if (start)
	{
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 100);
		SDL_RenderFillRect(renderer, &t);
	}
	if (end)
	{
		walls[right] = false;
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, 100);
		SDL_RenderFillRect(renderer, &t);
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (walls[top])
		SDL_RenderDrawLine(renderer, x, y, x + w, y);
	if (walls[right])
		SDL_RenderDrawLine(renderer, x + w, y, x + w, y + w);
	if (walls[bottom])
		SDL_RenderDrawLine(renderer, x + w, y + w, x, y + w);
	if (walls[left])
		SDL_RenderDrawLine(renderer, x, y + w, x, y);
}

void Cell::highlight(SDL_Renderer* renderer, int w, Uint8 r, Uint8 g, Uint8 b)
{
	int x = _i * w;
	int y = _j * w;
	SDL_SetRenderDrawColor(renderer, r, g, b, 0x100);
	SDL_Rect t = { x, y, w, w };
	SDL_RenderFillRect(renderer, &t);
}

void Cell::SetVisited(bool v)
{
	visited = v;
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

void Cell::Start()
{
	start = true;
}

void Cell::End()
{
	end = true;
}