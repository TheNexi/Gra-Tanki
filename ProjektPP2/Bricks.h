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
	
	sf::Texture texture;//obiekt klasy texture z biblioteki sfml
	sf::Sprite sprite;//obiekt klasy sprite z biblioteki sfml
	
	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml

	float destructionHp;

	void initVariables();
	void initTexture();
	void initSprite();

public:
	Bricks(float pos_x, float pos_y);
	virtual ~Bricks();

	//Metody do okreslania pozycji obiektu
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	//Modyfikatory do kolizji
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	void update();
	void render(sf::RenderTarget& target);


};

