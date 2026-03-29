#include "DayNightCycle.h"
#include "settings.h"

DayNightCycle::DayNightCycle() {
	currentTickTime = 0;
	totalTickTime = settings::dayNightTickLen;
	paused = false;
}

DayNightCycle::DayNightCycle(int initialTickTime) {
	currentTickTime = initialTickTime;
	totalTickTime = settings::dayNightTickLen;
	paused = false;
}

DayNightCycle::DayNightCycle(int initialTickTime, int totalCycleTicks) {
	currentTickTime = initialTickTime;
	totalTickTime = totalCycleTicks;
	paused = false;
}

DayNightCycle::DayNightCycle(int initialTickTime, int totalCycleTicks, bool isPaused) {
	currentTickTime = initialTickTime;
	totalTickTime = totalCycleTicks;
	paused = isPaused;
}

int DayNightCycle::getCurrentTickTime() {
	return currentTickTime;
}
int DayNightCycle::getTotalTickTime() {
	return totalTickTime;
}
bool DayNightCycle::isPaused() {
	return paused;
}
void DayNightCycle::setCurrentTickTime(int tickTime) {
	currentTickTime = tickTime;
}
void DayNightCycle::setTotalTickTime(int tickTime) {
	totalTickTime = tickTime;
}
void DayNightCycle::setPaused(bool shouldPause) {
	paused = shouldPause;
}

bool DayNightCycle::isDay() {
	return currentTickTime >= totalTickTime / 4 && currentTickTime < 3 * totalTickTime / 4;
}
bool DayNightCycle::isNight() {
	return !isDay();
}

void DayNightCycle::tick() {
	if (paused) return;

	if (currentTickTime == totalTickTime - 1) {
		currentTickTime = 0;
	}
	else {
		currentTickTime++;
	}
}

std::string DayNightCycle::getHour() {
	return std::to_string(24 * (currentTickTime / (float) totalTickTime));
}
std::string DayNightCycle::getMinute() {
	float progress = 24.0f * (currentTickTime / (float)totalTickTime);
	float hourProgress = progress - (int)progress;
	if (hourProgress * 60 < 10) {
		return "0" + std::to_string((int)(hourProgress * 60));
	}
	else return std::to_string((int)(hourProgress * 60));
}
std::string DayNightCycle::getTimeStr24() {
	std::string ret;
	ret += getHour();
	ret += ":";
	ret += getMinute();
	return ret;
}
std::string DayNightCycle::getTimeStr12() {
	std::string ret;
	char am;
	int hour = std::stoi(getHour());
	if (hour > 11) {
		am = 'p';
	}
	else am = 'a';

	if (hour == 0 || hour == 12)
		ret += "12";
	else
		ret += std::to_string(hour > 11 ? hour - 12 : hour);
	
	ret += ":";
	ret += getMinute();
	ret += am;

	return ret;
}