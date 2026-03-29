#include "MapPrinter.h"
#include <chrono>
#include <iomanip>

bool MapPrinter::saveEntireMapToFile(Map& map) {
	//Create render texture to draw to.  If error creating return false.
	sf::RenderTexture renderTexture;
	if (!renderTexture.create(map.getWidth() * settings::imagePixelSize, map.getHeight() * settings::imagePixelSize)) {
		//error...
		return false;
	}

	//Pixel for drawing
	sf::RectangleShape pixel(sf::Vector2f(settings::imagePixelSize, settings::imagePixelSize));
	renderTexture.clear();

	//Draw pixels
	for (int y = 0; y < map.getHeight(); y++) {
		for (int x = 0; x < map.getWidth(); x++) {
			//Render Algorithm, decide on what to do
			pixel.setFillColor(settings::textures.at(map.getPoint(x, y)));
			pixel.setPosition(sf::Vector2f(x * pixel.getSize().x, (map.getHeight() - y) * pixel.getSize().y));
			renderTexture.draw(pixel);
		}
	}

	//Get datetime for filename
	time_t in_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	struct tm currentLocalTime;
	localtime_s(&currentLocalTime, &in_time_t);
	std::string timestamp = std::to_string(currentLocalTime.tm_mon + 1) + "-" + std::to_string(currentLocalTime.tm_mday) + "-" + std::to_string(currentLocalTime.tm_year + 1900) + 
							"@" + std::to_string(currentLocalTime.tm_hour) + "-" + std::to_string(currentLocalTime.tm_min) + "-" + std::to_string(currentLocalTime.tm_sec);

	//Save
	renderTexture.getTexture().copyToImage().saveToFile("C:\\Users\\Andrew\\Desktop\\worldMap_" + timestamp + ".png");  //my own path since its just for me rn (6/10/2024 - 11:27pm)
	return true;
}