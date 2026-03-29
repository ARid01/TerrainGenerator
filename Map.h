#pragma once
#include <vector>

class Map {
private:
	short mapWidth;
	short mapHeight;
	std::vector<short> map;
	int sinSeed;

public:

	Map();
	Map(short width, short height);
	~Map();

	bool setPoint(short x, short y, short val);
	short getPoint(short x, short y);
	short getWidth();
	short getHeight();
	short getGroundLevel(short x);
	int getSinSeed();
	void setSinSeed(int nSinSeed);
};
