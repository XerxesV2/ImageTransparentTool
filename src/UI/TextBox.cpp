#include "TextBox.hpp"
#include "../Globals.hpp"
#include "Slider.hpp"
#include <iostream>
#include <chrono>
#include <ctime>  
#include <string>

TextBox::TextBox(sf::Font &font) : text("255", font, 50)
{
	//this->background.setSize(sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
	//this->background.setOrigin(this->text.getGlobalBounds().width / 2.f, this->text.getGlobalBounds().height / 2.f);
	//this->background.setFillColor(sf::Color::Blue);

	this->originalColor = this->text.getFillColor();
}

void TextBox::Update(sf::RenderWindow &window)
{
	if (this->wait1Tick) {	//bc the loop
		Global::waitingForinput = true;
		this->selected = true;
		this->wait1Tick = false;
	}

	if (this->selected) {
		sf::Color color = this->text.getFillColor();
		color.a = (100.f + sin(this->time.getElapsedTime().asSeconds() * 5.f) * 70.f);
		this->text.setFillColor(color);
		//				offset										speed		spread
		//std::cout << (50.f + sin(this->time.getElapsedTime().asSeconds() * 5.f) * 50.f) << std::endl;
	}
	if (Global::waitingForinput && this->selected) { GetInput(window); return; }

	if (!HasMouseInput()) return;
	if (Global::waitingForinput && this->text.getGlobalBounds().contains(GetCorrectedMousePos(window))) {
		this->wait1Tick = true;
	}
	else if(this->text.getGlobalBounds().contains(GetCorrectedMousePos(window))){
		Global::waitingForinput = true;
		this->selected = true;
	}
}

void TextBox::Draw(sf::RenderTarget& window)
{
	//window.draw(this->background); //no bc for now
	window.draw(this->text);
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
	while (window.pollEvent(this->event)) {
		static std::string tempVal;
		static int counter = 0;
		if (this->event.type == sf::Event::KeyPressed) {
			if (this->event.key.code >= sf::Keyboard::Num0 && this->event.key.code <= sf::Keyboard::Num9) {
				//std::cout << this->event.key.code << std::endl;

				if (counter >= 3) { counter = 0; tempVal.clear(); }
				tempVal += (this->event.key.code + 22);
				++counter;

				if(std::atoi(tempVal.c_str()) > 255) { --counter; tempVal.pop_back(); }
				
				this->newValue = std::atoi(tempVal.c_str());
				
				//...
				//this->text.setString(std::to_string(this->event.key.code));
			}
			else if (this->event.key.code == sf::Keyboard::BackSpace) {
				if (counter > 0) {
					--counter;
					tempVal.pop_back();
					this->newValue = std::atoi(tempVal.c_str());
				}
			}
			else if (this->event.key.code == sf::Keyboard::Enter) {
				Global::waitingForinput = false;
				this->selected = false;
				this->text.setFillColor(this->originalColor);
			}
		}

		if (this->event.type == sf::Event::MouseButtonPressed) {
			if (!this->text.getGlobalBounds().contains(GetCorrectedMousePos(window))) {
				Global::waitingForinput = false;
				this->selected = false;
				this->text.setFillColor(this->originalColor);
			}
		}

		if (sf::Event::Closed == event.type) {
			window.close();
		}
	}
}
