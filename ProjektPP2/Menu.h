#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;

#define MAX_NUMBER_OF_OPTIONS 2

class Menu
{
private:
	int selectedOptionIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_OPTIONS];

public:
	
	Menu(float width, float height);
	virtual ~Menu();

	void render(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getPressedOption();
	//void pollEvents(sf::RenderWindow& window);
};

