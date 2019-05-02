#include "main.h"

using namespace std;

Spot::Spot()
{
	i = 0;
	j = 0;
}

Spot::Spot(int _i, int _j)
{
	i = _i;
	j = _j;
}

Spot::~Spot()
{

}

void Spot::addNeighbors(vector<vector<Spot*>> s, int cols, int rows)
{
	if (i < cols - 1)
	{
		neighbors.push_back(s[(double)i + 1][(double)j]);
	}
	if (i > 0)
	{
		neighbors.push_back(s[(double)i - 1][(double)j]);
	}
	if (j < rows - 1)
	{
		neighbors.push_back(s[(double)i][(double)j + 1]);
	}
	if (j > 0)
	{
		neighbors.push_back(s[(double)i][(double)j - 1]);
	}
	if (i > 0 && j > 0)
	{
		neighbors.push_back(s[(double)i - 1][(double)j - 1]);
	}
	if (i < cols - 1 && j > 0)
	{
		neighbors.push_back(s[(double)i + 1][(double)j - 1]);
	}
	if (i > 0 && j < rows - 1)
	{
		neighbors.push_back(s[(double)i - 1][(double)j + 1]);
	}
	if (i < cols - 1 && j < rows - 1)
	{
		neighbors.push_back(s[(double)i + 1][(double)j + 1]);
	}
}