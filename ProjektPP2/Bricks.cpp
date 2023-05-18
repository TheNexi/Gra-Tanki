#include "Bricks.h"
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

Bricks::Bricks(sf::Texture* texture,float pos_x, float pos_y, float destructionHp)
{
	this->shape.setTexture(*texture); //tekstura obrazu pocisku
	
	this->shape.setOrigin(25, 25);
	this->shape.setPosition(pos_x, pos_y); // ustawienie pozycji cegly na ekranie
}

Bricks::~Bricks()
{

}


const sf::FloatRect Bricks::getBounds() const
{
	return this->shape.getGlobalBounds(); //Zwraca granice obiektu uwzglêdniaj¹c¹ pozycjê pocisku na ekranie
}


void Bricks::update()
{

}


void Bricks::render(sf::RenderWindow& window)
{
	window.draw(shape); // Wyœwietlanie ceg³y na ekranie
}
