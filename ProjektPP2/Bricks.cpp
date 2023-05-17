#include "Bricks.h"
#include <iostream>
using namespace std;


void Bricks::initVariables()
{
	this->destructionHp = 2.0f;

}

void Bricks::initTexture()
{
	//Wczytanie tekstury z pliku
	if (!this->texture.loadFromFile("Textures/cegla.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}
}

void Bricks::initSprite()
{
	//inicjacja tekstury do obiektu typu sprite
	this->sprite.setTexture(this->texture);
}

Bricks::Bricks(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->sprite.setOrigin(25, 25);
	this->sprite.setPosition(pos_x, pos_y); // ustawienie pozycji cegly na ekranie
}

Bricks::~Bricks()
{

}

const sf::Vector2f& Bricks::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Bricks::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bricks::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Bricks::setPosition(const float x, const float y)
{
	//Czy potrzebne?
	this->sprite.setPosition(x, y);
}

void Bricks::update()
{

}

void Bricks::render(sf::RenderTarget& target)//funkcja renderujaca obiekt 
{
	target.draw(this->sprite);

}
