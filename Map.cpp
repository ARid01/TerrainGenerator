#include "Map.h"
#include "settings.h"

Map::Map() {
	mapWidth = settings::defaultMapWidth;
	mapHeight = settings::defaultMapHeight;
	map = std::vector<short>(mapWidth * mapHeight, 0);
}
Map::Map(short width, short height) {
	mapWidth = width;
	mapHeight = height;
	map = std::vector<short>(mapWidth * mapHeight, 0);
}
Map::~Map() {
	map.~vector();
}

bool Map::setPoint(short x, short y, short val) {
	if (y * mapWidth + x >= map.size()) return false;
	map[y * mapWidth + x] = val;
	return true;
}
short Map::getPoint(short x, short y) {
	if (y * mapWidth + x >= map.size()) return -1;
	else return map[y * mapWidth + x];
}
short Map::getWidth() {
	return mapWidth;
}
short Map::getHeight() {
	return mapHeight;
}
short Map::getGroundLevel(short x) {
	//Finds first non air from top down
	int g = -1;
	for (int y = 0; y < mapHeight; y++) {
		if (getPoint(x, y) != 0) {
			g = y;
			break;
		}
	}
	return g;
}
int Map::getSinSeed() {
	return sinSeed;
}
void Map::setSinSeed(int nSinSeed) {
	sinSeed = nSinSeed;
}