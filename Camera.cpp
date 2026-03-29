#include "Camera.h"
#include "settings.h"

Camera::Camera() {
	x = settings::defCamX;
	y = settings::defCamY;
	halfWidth = settings::defCamHalfW;
	halfHeight = settings::defCamHalfH;
}
Camera::Camera(int nx, int ny) {
	x = nx;
	y = ny;
	halfWidth = settings::defCamHalfW;
	halfHeight = settings::defCamHalfH;
}
Camera::Camera(int nx, int ny, int halfW, int halfH) {
	x = nx;
	y = ny;
	halfWidth = halfW;
	halfHeight = halfH;
}

int Camera::getX() {
	return x;
}
int Camera::getY() {
	return y;
}
std::vector<int> Camera::getCoords() {
	return { x, y };
}
int Camera::getHalfWidth() {
	return halfWidth;
}
int Camera::getHalfHeight() {
	return halfHeight;
}

void Camera::setX(int nx) {
	x = nx;
}
void Camera::setY(int ny) {
	y = ny;
}
void Camera::setHalfWidth(int nhw) {
	halfWidth = nhw;
}
void Camera::setHalfHeight(int nhh) {
	halfHeight = nhh;
}

int Camera::getArea() {
	return (2 * halfWidth + 1) * (2 * halfHeight + 1);
}
void Camera::drawView(sf::RenderWindow& window, Map& map) {
	sf::RectangleShape pixel(sf::Vector2f(settings::resolutionWidth / (2 * halfWidth + 1), settings::resolutionHeight / (2 * halfHeight + 1)));

	for (int currY = y - halfHeight; currY <= y + halfHeight; currY++) {
		for (int currX = x - halfWidth; currX <= x + halfWidth; currX++) {
			pixel.setPosition(sf::Vector2f((currX - x + halfWidth) * pixel.getSize().x, (currY - y + halfHeight) * pixel.getSize().y));
			pixel.setFillColor(settings::textures.at(map.getPoint(currX, currY)));
			window.draw(pixel);
		}
	}
}

void Camera::moveUp() {
	if (y - halfHeight > 0) y--;
}
void Camera::moveDown(Map& map) {
	if (y + halfHeight < map.getHeight() - 1) y++;
}
void Camera::moveLeft() {
	if (x - halfWidth > 0) x--;
}
void Camera::moveRight(Map& map) {
	if (x + halfWidth < map.getWidth() - 1) x++;
}