#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace settings {
	constexpr int maxMsPerTick{ 50 }; //RELEASE: 50 - 20 TPS, DEBUG: ANY
	constexpr int resolutionWidth{ 700 };
	constexpr int resolutionHeight{ 700 };
	constexpr char windowName[] = "Test Window v0.0.3";

	//DayNightCycle
	constexpr int dayNightTickLen{ 2400 }; //2 Minutes

	//Map
	constexpr short defaultMapWidth{ 512 };
	constexpr short defaultMapHeight{ 256 };

	//Texture Map
	const std::unordered_map<short, sf::Color> textures{
		{0, {0, 0, 0}},				//air
		{1, {136, 140, 141}},		//stone
		{2, {163, 111, 13}},		//dirt
		{3, {44, 163, 13}},			//grass
		{4, {59, 59, 57}},			//coal
		{5, {227, 189, 172}},		//iron
		{6, {55, 216, 255}},		//diamond
		{7, {224, 17, 95}},			//ruby
		{8, {139, 105, 20}},		//wood
		{9, {52, 162, 3}},			//leaves
		{10, {28, 163, 236}}		//water
	};

	//Ore Probability
	const std::unordered_map<short, float> oreProbabilities{
		{4, 0.5f},
		{5, 0.2f},
		{6, 0.1f},
		{7, 0.2f}
	};

	const std::unordered_map<short, std::pair<short, short>> oreSpawnRanges{
		{4, {0.25 * defaultMapHeight, 0.6 * defaultMapHeight}},
		{5, {0.5 * defaultMapHeight, 0.9 * defaultMapHeight}},
		{6, {0.8 * defaultMapHeight, defaultMapHeight}},
		{7, {0.7 * defaultMapHeight, defaultMapHeight}}
	};

	//Ore Spawn Begin Probability
	constexpr float oreSpawnProb{ 0.016f };

	//Terrain Generation
	constexpr float terrainAmp{ 4.0f };
	constexpr float elevAmp{ 15.0f };
	constexpr float sinReducFac{ 0.05f };
	constexpr float sinReducFac_E{ 0.015f };
	constexpr short minTreeHeight{ 4 };
	constexpr short maxTreeHeight{ 10 };
	constexpr short minTreeDst{ 9 };
	constexpr float treeSpawnProb{ 0.0005f };
	constexpr int caveLevelPlusLand{ 8 };
	constexpr float caveOccupancyPercent{ 0.525f };
	constexpr int leavesReach{ 3 };
	constexpr float leavesSpawnProb{ 0.9f };
	constexpr float waterLakeProb{ 0.003f };
	constexpr short maxTerrainElevation{ 6 };

	//Camera Constants
	constexpr int defCamX{ 64 };
	constexpr int defCamY{ 64 };
	constexpr int defCamHalfW{ 17 };
	constexpr int defCamHalfH{ 17 };

	//Image saving
	constexpr int imagePixelSize{ 4 };

	//Entity Settings and Defaults
	const std::string defaultEntityName{ "Entity" };
	constexpr float defEntityMS{ 3.25f };
	constexpr float defEntityJF{ 1.0f };
}

namespace constants {
	constexpr double pi{ 3.14159265358979311599796346854 };
}
