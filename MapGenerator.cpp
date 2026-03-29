#include "MapGenerator.h"
#include "settings.h"


short MapGenerator::landDifference(short x, int sinSeed) {
	return settings::terrainAmp * (sin(settings::sinReducFac * 2 * x + sinSeed) + sin(settings::sinReducFac * constants::pi * x + 2 * (double)sinSeed));
}
short MapGenerator::elevation(short x, int sinSeed) {
	return settings::elevAmp * (sin(settings::sinReducFac_E * 2 * x + sinSeed) + sin(settings::sinReducFac_E * constants::pi * x + (double)sinSeed));
}
MapGenerator::MapGenerator() {
	mapWidth = settings::defaultMapWidth;
	mapHeight = settings::defaultMapHeight;
}
MapGenerator::MapGenerator(short width, short height) {
	mapWidth = width;
	mapHeight = height;
}
Map MapGenerator::Generate() {
	srand(time(nullptr));
	Map map(mapWidth, mapHeight);

	//Generation here
	//start generating stone halfway down
	short landLevel = mapHeight / 4 + (rand() % (mapHeight / 4) - mapHeight / 8);  // 1/8 -> 3/8 * mapheight Landlevel Range
	short peakElevationY = mapHeight;
	int stoneCount = 0;
	int sinSeed = rand();
	map.setSinSeed(sinSeed);

	for (short x = 0; x < mapWidth; x++) {
		short initLevel = landLevel + landDifference(x, sinSeed) + elevation(x, sinSeed); //max 19 above/below landlevel
		if (initLevel < settings::maxTerrainElevation) initLevel = settings::maxTerrainElevation;

		if (initLevel < peakElevationY) peakElevationY = initLevel;
		for (short y = initLevel; y < mapHeight; y++) {
			short dst = y - initLevel;

			if (dst == 0)
				map.setPoint(x, y, 3);
			else if (dst < 4)
				map.setPoint(x, y, 2);
			else {
				map.setPoint(x, y, 1);
				stoneCount++;
			}
		}
	}

	//Generate caves
	for (int i = 0; i < stoneCount * settings::caveOccupancyPercent; i++) {
		short x, y;
		do {
			x = rand() % mapWidth;
			short gl = map.getGroundLevel(x);
			y = rand() % (mapHeight + settings::caveLevelPlusLand - gl) + gl + settings::caveLevelPlusLand;
		} while (map.getPoint(x, y) == 0);

		map.setPoint(x, y, 0);
	}

	//Cellular automata
	for (char pass = 0; pass < 3; pass++) {
		//For each cell in range
		for (short x = 0; x < mapWidth; x++) {
			for (short y = map.getGroundLevel(x) + settings::caveLevelPlusLand; y < mapHeight; y++) {
				//Get neighbor count
				char neighbors = 0;
				if (x > 0 && map.getPoint(x - 1, y) == 0) neighbors++;
				if (x < mapWidth - 1 && map.getPoint(x + 1, y) == 0) neighbors++;
				if (y > 0 && map.getPoint(x, y - 1) == 0) neighbors++;
				if (y < mapHeight - 1 && map.getPoint(x, y + 1) == 0) neighbors++;
				if (x > 0 && y > 0 && map.getPoint(x - 1, y - 1) == 0) neighbors++;
				if (x < mapWidth - 1 && y > 0 && map.getPoint(x + 1, y - 1) == 0) neighbors++;
				if (x > 0 && y < mapHeight - 1 && map.getPoint(x - 1, y + 1) == 0) neighbors++;
				if (x < mapWidth - 1 && y < mapHeight - 1 && map.getPoint(x + 1, y + 1) == 0) neighbors++;

				if (map.getPoint(x, y) == 0 && neighbors >= 4) continue; //stays air
				else if (map.getPoint(x, y) != 0 && neighbors >= 5) map.setPoint(x, y, 0); //set to air
				else map.setPoint(x, y, 1); //stone otherwise
			}
		}
	}

	//Place ores -- work on the probability of the ore spawning linking with the spawn range stuff
	for (int i = 0; i < (mapWidth * (mapHeight - landLevel)) * settings::oreSpawnProb; i++) {
		short x, y;
		do {
			x = rand() % mapWidth;
			y = (rand() % (mapHeight - landLevel)) + landLevel;
		} while (map.getPoint(x, y) != 1);

		//x,y are stone
		std::vector<short> validOres;
		for (auto& it : settings::oreProbabilities) {
			short ore = it.first;
			if (isInRange(ore, y)) {
				short middleRange = (settings::oreSpawnRanges.at(ore).second - settings::oreSpawnRanges.at(ore).first) / 2 + settings::oreSpawnRanges.at(ore).first;
				for (int j = 0; j < abs(middleRange - y) / settings::oreProbabilities.at(ore); j++) {
					validOres.push_back(ore);
				}
			}
		}
		//Randomly select ore
		if (!validOres.empty()) {
			short randInd = rand() % validOres.size();
			map.setPoint(x, y, validOres[randInd]);
		}
	}

	//Grow trees!
	short lastPlacedTreeX = -1;
	for (short x = 0; x < mapWidth; x++) {
		if (2 * rand() / (RAND_MAX + 1) < settings::treeSpawnProb) {
			//Attempt tree spawn
			if (x - lastPlacedTreeX >= settings::minTreeDst) {
				//Place start tree
				short treeHeight = rand() % (settings::maxTreeHeight - settings::minTreeHeight) + settings::minTreeHeight;

				//Find ground level for x
				short groundLevel = map.getGroundLevel(x);
				if (groundLevel == -1 || map.getPoint(x, groundLevel) != 3) continue; //Skip if no land or grass on top

				//Plant the wood
				for (short y = treeHeight; y > 0; y--) {
					map.setPoint(x, groundLevel - 1 - (treeHeight - y), 8);

					if (y == 1) {
						//Last wood placed, add leaves

						//Leaves here
						for (float angle = 0; angle <= constants::pi; angle += constants::pi / 6) {
							for (float perc = 0; perc <= 1.0; perc += 0.1f) {
								short lx = x + cosf(angle) * perc * settings::leavesReach;
								short ly = groundLevel - 1 - (treeHeight - y) + sinf(angle * perc * settings::leavesReach);

								//Chance to spawn leaves
								if (map.getPoint(lx, ly) == 0 && rand() / RAND_MAX < settings::leavesSpawnProb) map.setPoint(lx, ly, 9);
							}
						}
					}
				}
				lastPlacedTreeX = x;
			}
		}
	}

	return map;
}

bool MapGenerator::isInRange(short ore, short y) {
	return y >= settings::oreSpawnRanges.at(ore).first && y < settings::oreSpawnRanges.at(ore).second;
}