//main.cpp
//Andrew Ridgely - 6/2/2024
//An attempt at a tick system

#include <chrono>
#include <thread>
#include "settings.h"
#include "DayNightCycle.h"
#include "MapGenerator.h"
#include "Camera.h"
#include "MapPrinter.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"

//Place holder for tick function, once i found out what i want to build
#include <iostream>
static unsigned long long tickCount = 0;  //With 50MS ticks, will overflow after 29,227,102,304.5 years.

void tick(const std::chrono::high_resolution_clock& clock, DayNightCycle& dnc) {
	std::chrono::time_point<std::chrono::high_resolution_clock> begin = clock.now();

	dnc.tick();

	int elapsedMillis = std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - begin).count();
	std::cout << "Tick Number: " << ++tickCount << ": elapsed in " << elapsedMillis << " ms.\n";
	std::cout << "Current Time: " << dnc.getTimeStr12() << ", it is " << (dnc.isDay() ? "day.\n" : "night.\n");
}
//End place holder

int main() {
	//Window Initialization
	sf::RenderWindow window(sf::VideoMode(settings::resolutionWidth, settings::resolutionHeight), settings::windowName);
	window.setFramerateLimit(144);
	
	//Debug pixel for now
	sf::RectangleShape pixel(sf::Vector2f(settings::resolutionWidth / settings::defaultMapWidth, settings::resolutionHeight / settings::defaultMapHeight));


	//Loading stuff here
	DayNightCycle dnc;
	MapGenerator mapGen;
	Map map = mapGen.Generate();
	
	//Set position at halfway point, ground level
	Camera camera(map.getWidth() / 2, map.getGroundLevel(map.getWidth() / 2));

	//Main loop stuff
	std::chrono::high_resolution_clock clock;

	std::chrono::time_point<std::chrono::high_resolution_clock> lastTimeFrame = clock.now();
	while (window.isOpen()) {
		//Check if tick is needed
		if (std::chrono::duration_cast<std::chrono::milliseconds>(clock.now() - lastTimeFrame).count() > settings::maxMsPerTick) {
			//Time for next tick
			tick(clock, dnc);
			lastTimeFrame = clock.now();
		}

		//Handle input
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				window.close();
		}

		//DEBUG
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			map = mapGen.Generate();
			camera.setY(map.getGroundLevel(camera.getX()));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			MapPrinter::saveEntireMapToFile(map);
		}

		//Move camera
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.moveUp();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.moveLeft();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.moveDown(map);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.moveRight(map);

		//Render
		window.clear();
		camera.drawView(window, map);
		window.display();
	}

	return 0;
}