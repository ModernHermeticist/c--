#pragma once
class Cell
{
public:
	Cell(int _xPos, int _yPos);
	~Cell();
	void Draw(SDL_Renderer* renderer, bool fill);
	void Highlight();
	void ResetColor();
	bool compareXandY(int x, int y);
	void ToggleSelected();
	bool Selected() { return selected; }
	void SetNeighbors(std::vector<Cell*> grid);

private:
	int xPos;
	int yPos;

	std::vector<Cell*> neighbors;

	bool selected;

	struct Color
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
	}col;
};

