#include <iostream>
#include <string>

using namespace std;

extern "C"
{
#include "../lua/include/lua.h"
#include "../lua/include/lauxlib.h"
#include "../lua/include/lualib.h"
#include "../sdl/include/SDL.h"
#include "../sdl/include/SDL_main.h"
}

#ifdef _WIN64
#pragma comment(lib, "../lua/liblua53.a")
#pragma comment(lib, "../sdl/lib/x64/SDL2.lib")
#pragma comment(lib, "../sdl/lib/x64/SDL2main.lib")
#endif

bool CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		string errormsg = lua_tostring(L, -1);
		cout << errormsg << endl;
		return false;
	}
	return true;
}

void LoadSettings(lua_State* L, int& SCREEN_WIDTH, int& SCREEN_HEIGHT, int& spotWidth, int& spotHeight)
{
	lua_getglobal(L, "SCREEN_WIDTH");
	if (lua_isnumber(L, -1))
		SCREEN_WIDTH = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "SCREEN_HEIGHT");
	if (lua_isnumber(L, -1))
		SCREEN_HEIGHT = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "spotWidth");
	if (lua_isnumber(L, -1))
		spotWidth = (int)lua_tonumber(L, -1);

	lua_getglobal(L, "spotHeight");
	if (lua_isnumber(L, -1))
		spotHeight = (int)lua_tonumber(L, -1);
}

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;

	int SCREEN_WIDTH = 400;
	int SCREEN_HEIGHT = 400;
	int spotWidth = 50;
	int spotHeight = 50;
	int rows = SCREEN_WIDTH / spotWidth;
	int cols = SCREEN_HEIGHT / spotHeight;

	cout << "Before loading from lua file:" << endl;
	cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << endl;
	cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << endl;
	cout << "spotWidth: " << spotWidth << endl;
	cout << "spotHeight: " << spotHeight << endl;
	cout << "rows: " << rows << endl;
	cout << "cols: " << cols << endl;

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	if (CheckLua(L, luaL_dofile(L, "stuff.lua")))
	{
		LoadSettings(L, SCREEN_WIDTH, SCREEN_HEIGHT, spotWidth, spotHeight);
	}

	cout << "After loading from lua file:" << endl;
	cout << "SCREEN_WIDTH: " << SCREEN_WIDTH << endl;
	cout << "SCREEN_HEIGHT: " << SCREEN_HEIGHT << endl;
	cout << "spotWidth: " << spotWidth << endl;
	cout << "spotHeight: " << spotHeight << endl;
	cout << "rows: " << rows << endl;
	cout << "cols: " << cols << endl;


	//system("PAUSE");
	lua_close(L);
	return 0;
}