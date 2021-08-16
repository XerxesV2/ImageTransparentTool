#include "Button.hpp"
#include "../Globals.hpp"
#include <iostream>
#define SCREEN_X sf::VideoMode::getDesktopMode().width
#define SCREEN_Y sf::VideoMode::getDesktopMode().height

//#define CHIT(x) (x.x - (1920 - (SCREEN_X/3)), x.y - (1080 - (SCREEN_Y/3)))

Button::Button(sf::Vector2f pos, sf::String str, sf::Font& font, unsigned size, short ID) :
			  playButtonText(str, font, size),
			  ID(ID)
{
	this->playButtonText.setOrigin(this->playButtonText.getGlobalBounds().width / 2.f, this->playButtonText.getGlobalBounds().height / 2.f);
	this->playButtonText.setPosition(pos);
	this->playButtonText.setFillColor(sf::Color(255, 255, 255, 255));
	this->playButtonText.setOutlineColor(sf::Color(100, 100, 100, 200));


	this->background.setSize(sf::Vector2f(this->playButtonText.getGlobalBounds().width + 40.f,
		this->playButtonText.getGlobalBounds().height + 20.f));
	this->background.setPosition(this->playButtonText.getGlobalBounds().left - 20.f,
		this->playButtonText.getGlobalBounds().top - 10.f);
	//this->background.setOrigin(this->background.getSize().x / 2.f, this->background.getSize().y / 2.f);
	this->background.setFillColor(sf::Color(100, 100, 100, 0));

}

void Button::UpdateHighlight(sf::RenderWindow& window)
{
	if (this->background.getGlobalBounds().contains(GetCorrectedMousePos(window))) {
		if (!isStateChanged) needUpdate = true;
		isStateChanged = true;
	}
	else { if (isStateChanged) needUpdate = true; isStateChanged = false; }

	if (!needUpdate) return;

	//this->playButtonText.setOutlineThickness(5.f * isStateChanged);
	this->background.setFillColor(sf::Color(100, 100, 100, 150 * isStateChanged));

	needUpdate = false;
}

int Button::IsClicked(sf::RenderWindow& window)
{
	if (this->background.getGlobalBounds().contains(sf::Vector2f(GetCorrectedMousePos(window)))) {
		return ID;
	}

	return -1;
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(this->background);
	window.draw(this->playButtonText);
}

Button::~Button()
{
}

bool Button::HasMouseInput()
{
	static bool isButtonAreadyPressed = false;
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { isButtonAreadyPressed = false; return 0; }
	if (isButtonAreadyPressed) return 0;
	isButtonAreadyPressed = true;
	return 1;
}
