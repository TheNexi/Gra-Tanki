/**
*
*@file Flag.h
*@brief Plik naglowkowy klasy Flag
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
/**
*
*@class Flag
*
*@brief Klasa reprezentujaca flage w grze.
*/
class Flag
{
private:
	sf::Texture texture;//obiekt klasy texture z biblioteki sfml /**< Obiekt klasy sf::Texture przechowuj�cy tekstur� flagi. */
	sf::Sprite sprite;//obiekt klasy sprite z biblioteki sfml /**< Obiekt klasy sf::Sprite reprezentuj�cy flag�. */

	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml /**< Obiekt klasy sf::Vector2f przechowuj�cy wsp�rz�dne flagi. */
	/**
   * @brief Inicjalizuje tekstur� flagi.
   */
	void initTexture();
	/**
	 * @brief Inicjalizuje sprite flagi.
	 */
	void initSprite();

public:
	/**
	* @brief Konstruktor klasy Flag.
	*/
	Flag();
	/**
	 * @brief Destruktor klasy Flag.
	 */
	virtual ~Flag();
	/**
	* @brief Ustawia pozycj� flagi na ekranie.
	* @param pos_x Wsp�rz�dna x pozycji flagi.
	* @param pos_y Wsp�rz�dna y pozycji flagi.
	*/
	void setPosition(float pos_x, float pos_y);
	/**
	* @brief Metoda zwracaj�ca granice flagi.
	* @return Obiekt klasy sf::FloatRect reprezentuj�cy granice flagi.
	*/
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)

	float destructionHp = 5;
	/**
	* @brief Metoda renderuj�ca flag� na oknie.
	* @param window Referencja do obiektu klasy sf::RenderWindow, reprezentuj�cego okno aplikacji.
	*/
	void render(sf::RenderWindow& window);

};

