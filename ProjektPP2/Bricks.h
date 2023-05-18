#pragma once
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace std;

class Bricks
{
private:
	sf::Sprite shape;//obiekt klasy sprite z biblioteki sfml
	
	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml

	float destructionHp;

public:
	Bricks(sf::Texture* texture, float pos_x, float pos_y, float destructionHp);
	virtual ~Bricks();

	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)

	void update(); //Metoda aktualizuj¹ca pozycjê pocisku na ekranie
	void render(sf::RenderWindow& window);
};

