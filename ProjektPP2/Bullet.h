/**

*@file Bullet.h
*@brief Plik nag³ówkowy klasy Bullet
*/
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

/**
*@class Bullet
*@brief Klasa reprezentuj¹ca pociski w grze.
*/
class Bullet
{
private:
	sf::Sprite shape; //Obiekt klasy Sprite przechowuj¹cy informacji o pocisku /< Obiekt klasy sf::Sprite przechowuj¹cy informacje o pocisku. */

	sf::Vector2f direction; //wektor kierunku ruchu pocisku /< Wektor kierunku ruchu pocisku. */
	float movementSpeed; //zmienna do prêdkoœci pocisku /**< Prêdkoœæ poruszania siê pocisku. */

public:
	std::string p_name; /**< Nazwa pocisku. */
	//Konstruktor
	/**
 * @brief Konstruktor klasy Bullet.
 * @param texture WskaŸnik na obiekt klasy sf::Texture przechowuj¹cy teksturê pocisku.
 * @param pos_x Wspó³rzêdna x pocz¹tkowej pozycji pocisku na ekranie.
 * @param pos_y Wspó³rzêdna y pocz¹tkowej pozycji pocisku na ekranie.
 * @param dir_x Sk³adowa x wektora kierunku ruchu pocisku.
 * @param dir_y Sk³adowa y wektora kierunku ruchu pocisku.
 * @param movement_speed Prêdkoœæ poruszania siê pocisku.
 * @param p_name Nazwa pocisku.
 */
	Bullet(sf::Texture* texture,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,std::string p_name); //Przyjmuje wskaŸnik do tekstury, pozycje pocz¹tkow¹, kierunek ruchu i prêdkoœæ
	
	
	//Destruktor
	/**
 * @brief Destruktor klasy Bullet.
 */
	virtual ~Bullet();
	/**
 * @brief Metoda zwracaj¹ca granice pocisku.
 * @return Obiekt klasy sf::FloatRect reprezentuj¹cy granice pocisku.
 */
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)
	/**
 * @brief Metoda aktualizuj¹ca pozycjê pocisku na ekranie.
 */
	void update(); //Metoda aktualizuj¹ca pozycjê pocisku na ekranie
	/**
 * @brief Metoda renderuj¹ca pocisk na docelowym renderowalnym obiekcie.
 * @param target WskaŸnik na obiekt klasy sf::RenderTarget, na którym ma zostaæ narysowany pocisk.
 */
	void render(sf::RenderTarget* target); //Metoda do rysowania pocisku na ekranie


};

