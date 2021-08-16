#pragma once
#include <SFML/Graphics.hpp>
#include "UI.hpp"
#include "Globals.hpp"

class Program
{
public:
	Program();

	void MainLoop();

	~Program();

private:
	void ModifieImage(sf::Color color);

	void Update();
	void Draw();

	void FileManagement();

	void HandleEvents();

private:
	// init list
	sf::RenderWindow window;
	sf::View view;
	UI ui;
	////////////

	sf::Event event;
	sf::Texture *ModdedTexture = nullptr, *OriginalTexture = nullptr;
	sf::Sprite  *ModdedSprite = nullptr;
	sf::Image image;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
};

