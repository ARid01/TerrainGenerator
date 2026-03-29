#pragma once
#include <string>

class Entity {
private:
	unsigned long long id;

	float x, y;
	std::string name;
	float moveSpeed;
	float jumpForce;
	bool grounded;

public:
	static unsigned long long EntityCount;

	Entity(float nx, float ny);
	Entity(float nx, float ny, std::string nName);
	Entity(float nx, float ny, std::string nName, float nMoveSpeed);
	Entity(float nx, float ny, std::string nName, float nMoveSpeed, float nJumpForce);

	float getX();
	float getY();
	unsigned long long getId();
	std::string getName();
	float getMoveSpeed();
	float getJumpForce();
	bool isGrounded();

	void setX(float nx);
	void setY(float ny);
	void setName(std::string nName);
	void setMoveSpeed(float nms);
	void setJumpForce(float njf);
};