#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;

class Flag
{
private:
	sf::Texture texture;//obiekt klasy texture z biblioteki sfml
	sf::Sprite sprite;//obiekt klasy sprite z biblioteki sfml

	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml

	void initTexture();
	void initSprite();

public:
	Flag();
	virtual ~Flag();

	void setPosition(float pos_x, float pos_y);

	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)

	float destructionHp = 5;
	void render(sf::RenderWindow& window);

};

