#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class CheckBox
{
public:
	CheckBox(sf::Vector2f pos, std::string text ,sf::Font &font);

	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderTarget &target);
	bool GetState() const;
	void SetState(bool state);

	~CheckBox();

private:
	sf::RectangleShape box;
	sf::RectangleShape marker;
	bool state = false;

	sf::Text text;
	sf::Font font;
};

