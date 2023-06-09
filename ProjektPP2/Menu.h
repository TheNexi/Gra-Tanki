#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;

#define MAX_NUMBER_OF_OPTIONS 3

class Menu
{
private:
	int selectedOptionIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_OPTIONS];
	sf::Texture background_texture;
	sf::RectangleShape background;


public:
	
	Menu(float width, float height);
	virtual ~Menu();

	void initBackground();
	void render(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getPressedOption();
};

