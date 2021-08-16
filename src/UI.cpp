#include "UI.hpp"
#include "Globals.hpp"

UI::UI(sf::RenderWindow &window) : window(window)
{
	this->font.loadFromFile("arial.ttf");
	this->InitButtons();
	this->InitSliders();
	this->InitCheckboxes();
}

void UI::Update()
{
	for (auto &i : this->buttons)
		i.UpdateHighlight(this->window);

	for (auto &i : this->sliders) 
		i.Update(this->window);

	if (!HasMouseInput()) return;
	for (auto &i : this->checkboxes)
		i.Update(this->window);

	UpdateCheckboxes();
}

void UI::UpdateCheckboxes()
{
	for (size_t i = 0; i < this->checkboxes.size(); i++)
	{
		if (i != currentActive && this->checkboxes.at(i).GetState() == true) {
			this->checkboxes.at(currentActive).SetState(false);
			currentActive = i;
			Global::NeedUpdate = true;
		}
	}
}

void UI::Draw()
{
	for (auto &i : this->buttons)
		i.Draw(this->window);

	for (auto &i : this->sliders) 
		i.Draw(this->window);

	for (auto &i : this->checkboxes)
		i.Draw(this->window);
	
}

sf::Color UI::GetColor()
{
	return sf::Color(this->sliders.at(0).GetValue(), this->sliders.at(1).GetValue(), this->sliders.at(2).GetValue(), 255);
}

int UI::GetActiveCheckbox()
{
	return this->currentActive;
}

int UI::IsButttonClicked()
{
	for (auto &i : this->buttons) {
		int ID = i.IsClicked(this->window);
		if (ID != -1) return ID;
	}
	return -1;
}

void UI::InitButtons()
{
	this->buttons.push_back(Button(sf::Vector2f(1800.f, 50.f), "Load", this->font, 60, LOAD));
	this->buttons.push_back(Button(sf::Vector2f(1800.f, 150.f), "Save", this->font, 60, SAVE));
}

void UI::InitSliders()
{
	this->sliders.push_back(Slider(sf::Vector2f(1650.f, 300.f), this->font));
	this->sliders.push_back(Slider(sf::Vector2f(1650.f, 400.f), this->font));
	this->sliders.push_back(Slider(sf::Vector2f(1650.f, 500.f), this->font));
	//this->sliders.push_back(Slider(sf::Vector2f(1650.f, 600.f), this->font));
}

void UI::InitCheckboxes()
{
	this->checkboxes.push_back(CheckBox(sf::Vector2f(1600.f, 600.f), ">", this->font)); this->checkboxes.back().SetState(true);
	this->checkboxes.push_back(CheckBox(sf::Vector2f(1700.f, 600.f), "<", this->font));
	this->checkboxes.push_back(CheckBox(sf::Vector2f(1800.f, 600.f), "=", this->font));
}

bool UI::HasMouseInput()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) { isButtonAreadyPressed = false; return 0; }
	if (isButtonAreadyPressed) return 0;
	isButtonAreadyPressed = true;
	return 1;
}

UI::~UI()
{
}
