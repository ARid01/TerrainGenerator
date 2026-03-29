#include "Entity.h"
#include "settings.h"

unsigned long long Entity::EntityCount = 1;

Entity::Entity(float nx, float ny) {
	id = EntityCount++;
	x = nx;
	y = ny;
	name = settings::defaultEntityName + std::to_string(id);
	moveSpeed = settings::defEntityMS;
	jumpForce = settings::defEntityJF;
}

Entity::Entity(float nx, float ny, std::string nName) {
	id = EntityCount++;
	x = nx;
	y = ny;
	name = nName;
	moveSpeed = settings::defEntityMS;
	jumpForce = settings::defEntityJF;
}
Entity::Entity(float nx, float ny, std::string nName, float nMoveSpeed) {
	id = EntityCount++;
	x = nx;
	y = ny;
	name = nName;
	moveSpeed = nMoveSpeed;
	jumpForce = settings::defEntityJF;
}
Entity::Entity(float nx, float ny, std::string nName, float nMoveSpeed, float nJumpForce) {
	id = EntityCount++;
	x = nx;
	y = ny;
	name = nName;
	moveSpeed = nMoveSpeed;
	jumpForce = nJumpForce;
}

float Entity::getX() {
	return x;
}
float Entity::getY() {
	return y;
}
unsigned long long Entity::getId() {
	return id;
}
std::string Entity::getName() {
	return name;
}
float Entity::getMoveSpeed() {
	return moveSpeed;
}
float Entity::getJumpForce() {
	return jumpForce;
}
bool Entity::isGrounded() {
	return grounded;
}

void Entity::setX(float nx) {
	x = nx;
}
void Entity::setY(float ny) {
	y = ny;
}
void Entity::setName(std::string nName) {
	name = nName;
}
void Entity::setMoveSpeed(float nms) {
	moveSpeed = nms;
}
void Entity::setJumpForce(float njf) {
	jumpForce = njf;
}