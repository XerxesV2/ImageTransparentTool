#include "TextBox.hpp"
#include "../Globals.hpp"
#include <iostream>

TextBox::TextBox(sf::Font &font) : text("EMPTY", font, 60)
{
	
}

void TextBox::Update(sf::RenderWindow &window)
{
	if (this->waitingForinput) { GetInput(window); return; }

	if (!HasMouseInput()) return;
	if (this->background.getGlobalBounds().contains(GetCorrectedMousePos(window))) {
		waitingForinput = !waitingForinput;
	}
}

bool TextBox::HasMouseInput()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { isButtonAreadyPressed = false; return 0; }
	if (isButtonAreadyPressed) return 0;
	isButtonAreadyPressed = true;
	return 1;
}

TextBox::~TextBox()
{
}

void TextBox::GetInput(sf::RenderWindow &window)
{
	window.pollEvent(this->event);

	if (this->event.type == sf::Event::KeyPressed) {
		if (this->event.key.code) {
			std::cout << this->event.key.code << std::endl;
		}
	}
}
