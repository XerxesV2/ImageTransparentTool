#pragma once
#include <SFML/Graphics.hpp>

#define WINDOWS_X 1920
#define WINDOWS_Y 1080

class Slider
{
public:
	Slider(sf::Vector2f pos, sf::Font &font);

	void Update(sf::RenderWindow &);
	int GetValue();
	void Draw(sf::RenderTarget &);

	~Slider();


private:
	bool holding = false;
	sf::RectangleShape bar;
	sf::CircleShape button;
	sf::Text valueText;
};

