#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map.h"

class Camera {
private:
	int x, y; //center
	int halfWidth; // 7 + 7 + 1 (center) = 15
	int halfHeight;

public:
	Camera();
	Camera(int nx, int ny);
	Camera(int nx, int ny, int halfW, int halfH);

	int getX();
	int getY();
	std::vector<int> getCoords();
	int getHalfWidth();
	int getHalfHeight();

	void setX(int nx);
	void setY(int ny);
	void setHalfWidth(int nhw);
	void setHalfHeight(int nhh);

	int getArea();
	void drawView(sf::RenderWindow &window, Map& map);

	void moveUp();
	void moveDown(Map& map);
	void moveLeft();
	void moveRight(Map& map);
};