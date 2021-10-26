#pragma once
#include <SFML/Graphics.hpp>

class Slider;
class TextBox
{
public:
	TextBox(sf::Font &font);

	void SetPos(sf::Vector2f pos) { background.setPosition(pos); text.setPosition(pos); }
	void SetText(std::string txt) { text.setString(txt); }
	sf::Text& GetText() { return this->text; }
	int GetNewValue() { if (this->newValue != -1) { return this->newValue; } else return -1; }
	void ResetNewValue() { this->newValue = -1; }

	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderTarget &window);

	bool HasMouseInput();
	~TextBox();

private:
	void GetInput(sf::RenderWindow &window);

private:

	sf::RectangleShape background;
	sf::Text text;
	sf::Event event;
	sf::Clock time;

	bool selected = false;
	bool isButtonAreadyPressed = false;
	bool wait1Tick = false;

	int newValue = -1;

	sf::Color originalColor;
};

