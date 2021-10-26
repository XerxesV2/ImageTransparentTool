#include "Slider.hpp"
#include "../Globals.hpp"
#include <iostream>
#include <math.h>

Slider::Slider(sf::Vector2f pos, sf::Font &font) : valueTextBox(font)
{
	//TODO
	this->bar.setSize(sf::Vector2f(255.f, 16.f));
	this->bar.setOrigin(150.f, 8.f);
	this->bar.setFillColor(sf::Color(120, 120, 120, 200));
	this->bar.setPosition(pos);

	this->button.setRadius(25.f);
	this->button.setOrigin(25.f, 25.f);
	this->button.setFillColor(sf::Color(200, 200, 200, 255));
	this->button.setPosition(bar.getGlobalBounds().left + 100.f, pos.y);

	this->valueTextBox.SetPos(sf::Vector2f((this->bar.getGlobalBounds().left + this->bar.getGlobalBounds().width) + 50.f, this->bar.getGlobalBounds().top -25.f));
}

void Slider::Update(sf::RenderWindow &window)
{	
	this->valueTextBox.Update(window);
	this->setValue(this->valueTextBox.GetNewValue());

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { holding = false; return; }
	if (!holding && !this->button.getGlobalBounds().contains(sf::Vector2f(GetCorrectedMousePos(window)))) return;
	holding = true;

	this->button.setPosition(static_cast<float>(std::max((int)(this->bar.getPosition().x -
		(this->bar.getSize().x / 2)), std::min((int)GetCorrectedMousePos(window).x,
		(int)(this->bar.getPosition().x + (this->bar.getSize().x / 2))))), this->button.getPosition().y);		//wow man thats looks shit
}

int Slider::GetValue()	//Is there any other better way to do this?
{
	int value = (int)std::floor((this->button.getPosition().x - (this->bar.getPosition().x - (this->bar.getSize().x / 2)))) + 1;
	this->valueTextBox.SetText(std::to_string(value));
	return value;
}

void Slider::setValue(int val)
{
	if (val == -1) return;
	int value = (int)std::floor((this->button.getPosition().x - (this->bar.getPosition().x - (this->bar.getSize().x / 2)))) + 1;
	this->button.setPosition((this->button.getPosition().x - value) + val, this->button.getPosition().y);
	this->valueTextBox.SetText(std::to_string(val));
	this->valueTextBox.ResetNewValue();
}

Slider::~Slider()
{
}

void Slider::Draw(sf::RenderTarget &window)
{
	this->valueTextBox.Draw(window);
	window.draw(this->bar);
	window.draw(this->button);
}
