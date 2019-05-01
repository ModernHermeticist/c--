#pragma once
#ifndef SPOT_H
#define SPOT_H

using namespace std;

class Spot
{
public:
	Spot();
	Spot(int _i, int _j);
	~Spot();

	int i = 0;
	int j = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	bool wall = false;
	vector<Spot*> neighbors;
	Spot* previous = nullptr;

	void addNeighbors(vector<vector<Spot>> &s, int cols, int rows);

private:
};

#endif