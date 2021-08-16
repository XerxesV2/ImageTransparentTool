#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::Vector2f, sf::String, sf::Font&, unsigned, short ID);

	void UpdateHighlight(sf::RenderWindow&);
	void Draw(sf::RenderWindow& window);
	int IsClicked(sf::RenderWindow&);

	inline sf::Text& GetText() { return this->playButtonText; }

	~Button();

private:
	sf::Text playButtonText;
	sf::RectangleShape background;
	short ID;

	///////for Highlights/////////
	bool needUpdate = false;
	bool isStateChanged = false;

public:
	static bool HasMouseInput();
};

