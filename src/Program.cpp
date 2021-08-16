#include "Program.hpp"
#include "FileManager.hpp"
#include <iostream>

#define SCREEN_X sf::VideoMode::getDesktopMode().width
#define SCREEN_Y sf::VideoMode::getDesktopMode().height

Program::Program() :
	window(sf::VideoMode(SCREEN_X / 2, SCREEN_Y / 2), "PTT", sf::Style::Close),
	view(sf::Vector2f(1920/2, 1080/2), sf::Vector2f(1920, 1080)),
	ui(window)
{
	this->window.setFramerateLimit(60);
	this->window.setView(this->view);

	this->backgroundTexture.loadFromFile("background.jpg");
	this->backgroundTexture.setRepeated(true);
}

void Program::MainLoop()
{
	while (this->window.isOpen()) {
		this->Update();
		this->Draw();
		//std::cout << Global::NeedUpdate << std::endl;
	}
}

void Program::ModifieImage(sf::Color color) 
{
	if (!Global::NeedUpdate) return;
	if (ModdedSprite == nullptr) { Global::NeedUpdate = false; return; }

	this->image =  this->OriginalTexture->copyToImage();
	
	uint32_t width = this->image.getSize().x;
	uint32_t height = this->image.getSize().y;

	sf::Color PixelColor;
	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			PixelColor = this->image.getPixel(x, y);

			switch (ui.GetActiveCheckbox())
			{
			case 0: if (PixelColor.r > color.r && PixelColor.g > color.g && PixelColor.b > color.b)
						this->image.setPixel(x, y, sf::Color(0, 0, 0, 0));
					break;

			case 1: if (PixelColor.r < color.r && PixelColor.g < color.g && PixelColor.b < color.b)
						this->image.setPixel(x, y, sf::Color(0, 0, 0, 0));
					break;

			case 2: if (PixelColor.r == color.r && PixelColor.g == color.g && PixelColor.b == color.b)
						this->image.setPixel(x, y, sf::Color(0, 0, 0, 0));
					break;
			
			default: break;
			}
			
		}
	}

	this->ModdedTexture->loadFromImage(this->image);
	Global::NeedUpdate = false;
}

void Program::Update()
{
	this->HandleEvents();
	if (!this->window.hasFocus()) return;

	this->ui.Update();
	this->FileManagement();

	static sf::Color LastColor = ui.GetColor();
	static sf::Color CurrentColor;
	CurrentColor = ui.GetColor();
	if (LastColor != CurrentColor) { Global::NeedUpdate = true;  LastColor = CurrentColor; }
	this->ModifieImage(CurrentColor);
}

void Program::Draw()
{
	this->window.clear(sf::Color(20, 20, 20, 255));

	this->window.draw(this->backgroundSprite);
	if(this->ModdedSprite != nullptr) this->window.draw(*this->ModdedSprite);

	this->ui.Draw();

	this->window.display();
}

void Program::FileManagement()
{
	if (!Button::HasMouseInput()) return;
	int ID = ui.IsButttonClicked();
	if (ID == -1) return;

	if (ID == UI::LOAD) {
		std::string path = FileManager::OpenFile();
		if (path == "error") return;
		if (this->OriginalTexture != nullptr) {
			delete OriginalTexture, ModdedTexture, ModdedSprite;
		}
		this->OriginalTexture = new sf::Texture();
		this->ModdedTexture = new sf::Texture();
		this->ModdedSprite = new sf::Sprite();

		this->OriginalTexture->loadFromFile(path);
		this->ModdedTexture->loadFromFile(path);
		this->ModdedSprite->setTexture(*this->ModdedTexture);

		sf::Vector2u textureSize = this->OriginalTexture->getSize();
		if (textureSize.x > 1400u) {
			float scaleFactor = 1400.f / (float)textureSize.x;
			this->ModdedSprite->setScale(scaleFactor, scaleFactor);
			this->backgroundSprite.setScale(scaleFactor, scaleFactor);
		}
		else if (textureSize.y > 1080u) {
			float scaleFactor = 1080.f / (float)textureSize.y;
			this->ModdedSprite->setScale(scaleFactor, scaleFactor);
			this->backgroundSprite.setScale(scaleFactor, scaleFactor);
		}

		this->backgroundSprite.setTexture(this->backgroundTexture);
		this->backgroundSprite.setTextureRect(sf::IntRect( 0, 0, this->OriginalTexture->getSize().x, this->OriginalTexture->getSize().y ));

		Global::NeedUpdate = true;
	}
	else if (ID == UI::SAVE) {
		std::string path = FileManager::SaveFile();
		if (path == "error") return;
		image.saveToFile(path);
		Global::NeedUpdate = true;
	}
}

void Program::HandleEvents()
{
	while (this->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->window.close();
		}
		if (sf::Event::Resized == event.type) {
			this->window.setView(this->view);
		}
	}
}

Program::~Program()
{
}
