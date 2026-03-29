#pragma once
#include "Map.h"

class MapGenerator {
private:
	short mapWidth;
	short mapHeight;

public:
	MapGenerator();
	MapGenerator(short width, short height);

	Map Generate();
	bool isInRange(short ore, short y);
	short landDifference(short x, int sinSeed);
	short elevation(short x, int sinSeed);
};