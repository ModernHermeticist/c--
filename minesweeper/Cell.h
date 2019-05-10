#pragma once
class Cell
{
public:
	Cell(int _xPos, int _yPos);
	~Cell();
	void Draw(SDL_Renderer* renderer, bool fill);
	void Highlight();
	bool compareXandY(int x, int y);

private:
	int xPos;
	int yPos;

	struct Color
	{
		Uint8 r;
		Uint8 g;
		Uint8 b;
	}col;
};

