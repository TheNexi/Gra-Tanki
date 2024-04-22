/**
*
*@file Menu.h
*@brief Plik naglowkowy klasy Menu
*/

#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;

#define MAX_NUMBER_OF_OPTIONS 2

/**
 * @class Menu
 * @brief Klasa reprezentujaca menu w grze.
 *
 * Klasa Menu odpowiada za wyswietlanie i obsluge menu w grze.
 * Pozwala na poruszanie siê po opcjach menu i zwraca wybran¹ opcje.
 */

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

