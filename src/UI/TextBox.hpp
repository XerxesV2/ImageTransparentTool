#pragma once
#include <SFML/Graphics.hpp>

class TextBox
{
public:
	TextBox(sf::Font &font);

	void SetPos(sf::Vector2f pos) { background.setPosition(pos); text.setPosition(pos); }
	void Update(sf::RenderWindow &window);

	bool HasMouseInput();
	~TextBox();

private:
	void GetInput(sf::RenderWindow &window);

private:

	sf::RectangleShape background;
	sf::Text text;
	sf::Event event;

	bool waitingForinput = false;
	bool isButtonAreadyPressed = false;
};

