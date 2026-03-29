#pragma once
#include <string>

class DayNightCycle {
private:
	int currentTickTime;
	int totalTickTime;
	bool paused;

public:
	DayNightCycle();
	DayNightCycle(int initialTickTime);
	DayNightCycle(int initalTickTime, int totalCycleTicks);
	DayNightCycle(int initalTickTime, int totalCycleTicks, bool isPaused);
	
	int getCurrentTickTime();
	void setCurrentTickTime(int tickTime);
	int getTotalTickTime();
	void setTotalTickTime(int tickTime);
	bool isPaused();
	void setPaused(bool shouldPause);

	void tick();

	bool isDay();
	bool isNight();

	std::string getHour();
	std::string getMinute();
	std::string getTimeStr24();
	std::string getTimeStr12();
};