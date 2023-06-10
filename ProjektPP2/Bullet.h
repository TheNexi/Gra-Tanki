#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class Bullet
{
private:
	sf::Sprite shape; //Obiekt klasy Sprite przechowuj¹cy informacji o pocisku

	sf::Vector2f direction; //wektor kierunku ruchu pocisku
	float movementSpeed; //zmienna do prêdkoœci pocisku

public:
	std::string p_name;
	//Konstruktor
	Bullet(sf::Texture* texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,std::string p_name); //Przyjmuje wskaŸnik do tekstury, pozycje pocz¹tkow¹, kierunek ruchu i prêdkoœæ
	
	
	//Destruktor
	virtual ~Bullet();
	
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)

	void update(); //Metoda aktualizuj¹ca pozycjê pocisku na ekranie
	void render(sf::RenderTarget* target); //Metoda do rysowania pocisku na ekranie


};

