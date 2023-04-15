#include "Bullet.h"


Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed) //konstuktor klasy Bullet do tworzenia obiektu pocisku
{
	this->shape.setTexture(*texture); //tekstura obrazu pocisku

	this->shape.setPosition(pos_x, pos_y); //pozycja pocisku z przekazanych parametrów
	this->direction.x = dir_x; //przypisanie kierunku x przekazanego przez parametr do wektora direction
	this->direction.y = dir_y; //przypisanie kierunku y przekazanego przez parametr do wektora direction
	this->movementSpeed = movement_speed; //predkosc pocisku z przekazanego parametru

}

Bullet::~Bullet() //Destruktor
{

}

const sf::FloatRect Bullet::getBounds() const //Metoda do granic obiektu(prostokatu)
{
	return this->shape.getGlobalBounds(); //Zwraca granice obiektu uwzglêdniaj¹c¹ pozycjê pocisku na ekranie
}

void Bullet::update()
{
	//Poruszanie pocisku
	this->shape.move(this->movementSpeed * this->direction); //Wektor przesuniecia pocisku odpowiadajacy predkosci i kierunku

}

void Bullet::render(sf::RenderTarget* target) //Metoda do rysowania pocisku na ekranie
{
	target->draw(this->shape); //wywo³anie funkcji wyswietlajacej pocisk (target) na ekranie

}
