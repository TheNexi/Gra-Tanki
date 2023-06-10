/**

*@file Bullet.h
*@brief Plik nag��wkowy klasy Bullet
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

/**
*@class Bullet
*@brief Klasa reprezentuj�ca pociski w grze.
*/
class Bullet
{
private:
	sf::Sprite shape; //Obiekt klasy Sprite przechowuj�cy informacji o pocisku /< Obiekt klasy sf::Sprite przechowuj�cy informacje o pocisku. */

	sf::Vector2f direction; //wektor kierunku ruchu pocisku /< Wektor kierunku ruchu pocisku. */
	float movementSpeed; //zmienna do pr�dko�ci pocisku /**< Pr�dko�� poruszania si� pocisku. */

public:
	std::string p_name; /**< Nazwa pocisku. */
	//Konstruktor
	/**
 * @brief Konstruktor klasy Bullet.
 * @param texture Wska�nik na obiekt klasy sf::Texture przechowuj�cy tekstur� pocisku.
 * @param pos_x Wsp�rz�dna x pocz�tkowej pozycji pocisku na ekranie.
 * @param pos_y Wsp�rz�dna y pocz�tkowej pozycji pocisku na ekranie.
 * @param dir_x Sk�adowa x wektora kierunku ruchu pocisku.
 * @param dir_y Sk�adowa y wektora kierunku ruchu pocisku.
 * @param movement_speed Pr�dko�� poruszania si� pocisku.
 * @param p_name Nazwa pocisku.
 */
	Bullet(sf::Texture* texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,std::string p_name); //Przyjmuje wska�nik do tekstury, pozycje pocz�tkow�, kierunek ruchu i pr�dko��
	
	
	//Destruktor
	/**
 * @brief Destruktor klasy Bullet.
 */
	virtual ~Bullet();
	/**
 * @brief Metoda zwracaj�ca granice pocisku.
 * @return Obiekt klasy sf::FloatRect reprezentuj�cy granice pocisku.
 */
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)
	/**
 * @brief Metoda aktualizuj�ca pozycj� pocisku na ekranie.
 */
	void update(); //Metoda aktualizuj�ca pozycj� pocisku na ekranie
	/**
 * @brief Metoda renderuj�ca pocisk na docelowym renderowalnym obiekcie.
 * @param target Wska�nik na obiekt klasy sf::RenderTarget, na kt�rym ma zosta� narysowany pocisk.
 */
	void render(sf::RenderTarget* target); //Metoda do rysowania pocisku na ekranie


};

