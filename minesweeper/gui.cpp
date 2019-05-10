#include "main.h"

void drawGenericRect(SDL_Renderer* renderer, int xPos, int yPos, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool fill)
{
	SDL_Rect rect{ xPos, yPos, width, height };
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	if (fill) SDL_RenderFillRect(renderer, &rect);
	else SDL_RenderDrawRect(renderer, &rect);
}

void drawBorder(SDL_Renderer* renderer, int cellHeight, int cellWidth)
{
	drawGenericRect(renderer, 0, 0, SCREEN_WIDTH, cellHeight, 0x0, 0xFF, 0xA0, 0xFF, true);
	drawGenericRect(renderer, 0, SCREEN_HEIGHT - cellHeight, SCREEN_WIDTH, cellHeight, 0x0, 0xFF, 0xA0, 0xFF, true);
	drawGenericRect(renderer, 0, 0, cellWidth, SCREEN_HEIGHT, 0x0, 0xFF, 0xA0, 0xFF, true);
	drawGenericRect(renderer, SCREEN_WIDTH - cellWidth, 0, cellWidth, SCREEN_HEIGHT, 0x0, 0xFF, 0xA0, 0xFF, true);
}