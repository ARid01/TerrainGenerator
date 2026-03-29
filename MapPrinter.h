#pragma once
#include "SFML/Graphics.hpp"
#include "settings.h"
#include "Map.h"

class MapPrinter {
public:
	static bool saveEntireMapToFile(Map& map);
};