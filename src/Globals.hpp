#pragma once
#include <SFML/Graphics.hpp>

sf::Vector2f GetCorrectedMousePos(sf::RenderWindow& window);

namespace Global {
	extern bool NeedUpdate;
	extern bool waitingForinput;
}