/**
*@file Bricks.h
*@brief Plik naglowkowy klasy Bricks
*/
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
	sf::Sprite shape;//obiekt klasy sprite z biblioteki sfml /< Obiekt klasy sf::Sprite reprezentuj�cy klocek. */
	
	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml /< Obiekt klasy sf::Vector2f przechowuj�cy wsp�rz�dne klocka. */ /**< Liczba punkt�w zdrowia okre�laj�ca, ile razy klocek mo�e zosta� trafiony przed zniszczeniem. */

	
	/**
* @brief Konstruktor klasy Bricks.
* @param texture Wska�nik na obiekt klasy sf::Texture przechowuj�cy tekstur� klocka.
* @param pos_x Wsp�rz�dna x po�o�enia klocka na ekranie.
* @param pos_y Wsp�rz�dna y po�o�enia klocka na ekranie.
* @param destructionHp Liczba punkt�w zdrowia klocka (domy�lnie: 2).
*/
public:
	Bricks(sf::Texture* texture, float pos_x, float pos_y, float destructionHp);
	/**
 * @brief Destruktor klasy Bricks.
 */
	virtual ~Bricks();
	/**
 * @brief Metoda zwracaj�ca granice klocka.
 * @return Obiekt klasy sf::FloatRect reprezentuj�cy granice klocka.
 */
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)
	/**
 * @brief Metoda zwracaj�ca granice klocka.
 * @return Obiekt klasy sf::FloatRect reprezentuj�cy granice klocka.
 */
	float destructionHp = 2;
	/**
 * @brief Metoda aktualizuj�ca pozycj� klocka na ekranie.
 */
	void update(); //Metoda aktualizuj�ca pozycj� pocisku na ekranie
	/**
 * @brief Metoda renderuj�ca klocek na oknie.
 * @param window Referencja do obiektu klasy sf::RenderWindow reprezentuj�cego okno aplikacji.
 */
	void render(sf::RenderWindow& window);
};

