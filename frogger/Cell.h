#pragma once
class Cell
{
public:
	Cell(int _xPos, int _yPos);
	~Cell();

	void Draw(SDL_Renderer* renderer, bool fill, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

private:
	int xPos;
	int yPos;
};

