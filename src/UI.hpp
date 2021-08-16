#pragma once
#include <vector>
#include "UI/Button.hpp"
#include "UI/Slider.hpp"
#include "UI/CheckBox.hpp"

class UI
{
public:
	UI(sf::RenderWindow &window);
	void Update();
	void UpdateCheckboxes();
	void Draw();

	sf::Color GetColor();
	int GetActiveCheckbox();
	int IsButttonClicked();

	void InitButtons();
	void InitSliders();
	void InitCheckboxes();

	bool HasMouseInput();
	~UI();

public:
	enum IDS { LOAD = 1, SAVE };

private:
	sf::RenderWindow &window;

	std::vector<Button> buttons;
	std::vector<Slider> sliders;
	std::vector<CheckBox> checkboxes;
	int currentActive = 0;

	sf::Font font;

	bool isButtonAreadyPressed = false;
};

