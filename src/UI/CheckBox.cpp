#include "CheckBox.hpp"
#include "../Globals.hpp"
#include <iostream>
CheckBox::CheckBox(sf::Vector2f pos, std::string text, sf::Font &font) : text(text, font, 50)
{
	this->box.setSize(sf::Vector2f(50.f, 50.f));
	this->box.setPosition(pos);
	this->box.setFillColor(sf::Color(60, 60, 60, 255));

	this->marker.setSize(sf::Vector2f(40.f, 40.f));
	this->marker.setPosition(pos + sf::Vector2f(5.f, 5.f));
	this->marker.setFillColor(sf::Color(30, 30, 30, 0));

	this->text.setPosition(pos + sf::Vector2f(5.f, 55.f));
}

void CheckBox::Update(sf::RenderWindow &window)
{
	if (!this->box.getGlobalBounds().contains(sf::Vector2f(GetCorrectedMousePos(window)))) return;

	//this->state = !this->state;
	this->state = true;
	this->marker.setFillColor(sf::Color(30, 30, 30, 255 * this->state));
}

void CheckBox::Draw(sf::RenderTarget &target)
{
	target.draw(this->box);
	target.draw(this->marker);
	target.draw(this->text);
}

bool CheckBox::GetState() const
{
	return this->state;
}

void CheckBox::SetState(bool state)
{
	this->state = state;
	this->marker.setFillColor(sf::Color(30, 30, 30, 255 * this->state));
}

CheckBox::~CheckBox()
{
}
