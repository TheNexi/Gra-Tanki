#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
private:
	sf::Sprite shape; //Obiekt klasy Sprite przechowuj�cy informacji o pocisku

	sf::Vector2f direction; //wektor kierunku ruchu pocisku
	float movementSpeed; //zmienna do pr�dko�ci pocisku

public:
	//Konstruktor
	Bullet(sf::Texture* texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed); //Przyjmuje wska�nik do tekstury, pozycje pocz�tkow�, kierunek ruchu i pr�dko��

	//Destruktor
	virtual ~Bullet();
	
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)

	void update(); //Metoda aktualizuj�ca pozycj� pocisku na ekranie
	void render(sf::RenderTarget* target); //Metoda do rysowania pocisku na ekranie


};

