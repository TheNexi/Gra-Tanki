#include "Flag.h"

void Flag::initTexture()
{
	if (!this->texture.loadFromFile("Textures/flag1.jpg"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki flagi" << endl;
	}
}

void Flag::initSprite()
{
	//inicjacja tekstury do obiektu typu sprite
	this->sprite.setTexture(this->texture);

}

Flag::Flag()
{
	this->initTexture();
	this->initSprite();
}

Flag::~Flag()
{

}

void Flag::setPosition(const float x, const float y)//ustawia pozycje poprzed dwie zmienne
{
	this->sprite.setPosition(x, y);

}

const sf::FloatRect Flag::getBounds() const
{
	return this->sprite.getGlobalBounds(); //Zwraca granice obiektu uwzglêdniaj¹c¹ pozycjê pocisku na ekranie
}

void Flag::render(sf::RenderWindow& window)
{
	window.draw(sprite); // Wyœwietlanie ceg³y na ekranie
}
