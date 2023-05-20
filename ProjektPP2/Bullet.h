#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Bullet
{
private:
	sf::Sprite shape; //Obiekt klasy Sprite przechowujący informacji o pocisku

	sf::Vector2f direction; //wektor kierunku ruchu pocisku
	float movementSpeed; //zmienna do prędkości pocisku

public:
	//Konstruktor
	Bullet(sf::Texture* texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed); //Przyjmuje wskaźnik do tekstury, pozycje początkową, kierunek ruchu i prędkość

	//Destruktor
	virtual ~Bullet();
	
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)

	void update(); //Metoda aktualizująca pozycję pocisku na ekranie
	void render(sf::RenderTarget* target); //Metoda do rysowania pocisku na ekranie


};

