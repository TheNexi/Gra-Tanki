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
	sf::Sprite shape;//obiekt klasy sprite z biblioteki sfml /< Obiekt klasy sf::Sprite reprezentuj¹cy klocek. */
	
	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml /< Obiekt klasy sf::Vector2f przechowuj¹cy wspó³rzêdne klocka. */ /**< Liczba punktów zdrowia okreœlaj¹ca, ile razy klocek mo¿e zostaæ trafiony przed zniszczeniem. */

	
	/**
* @brief Konstruktor klasy Bricks.
* @param texture WskaŸnik na obiekt klasy sf::Texture przechowuj¹cy teksturê klocka.
* @param pos_x Wspó³rzêdna x po³o¿enia klocka na ekranie.
* @param pos_y Wspó³rzêdna y po³o¿enia klocka na ekranie.
* @param destructionHp Liczba punktów zdrowia klocka (domyœlnie: 2).
*/
public:
	Bricks(sf::Texture* texture, float pos_x, float pos_y, float destructionHp);
	/**
 * @brief Destruktor klasy Bricks.
 */
	virtual ~Bricks();
	/**
 * @brief Metoda zwracaj¹ca granice klocka.
 * @return Obiekt klasy sf::FloatRect reprezentuj¹cy granice klocka.
 */
	const sf::FloatRect getBounds() const; ////Metoda do granic obiektu(prostokatu)
	/**
 * @brief Metoda zwracaj¹ca granice klocka.
 * @return Obiekt klasy sf::FloatRect reprezentuj¹cy granice klocka.
 */
	float destructionHp = 2;
	/**
 * @brief Metoda aktualizuj¹ca pozycjê klocka na ekranie.
 */
	void update(); //Metoda aktualizuj¹ca pozycjê pocisku na ekranie
	/**
 * @brief Metoda renderuj¹ca klocek na oknie.
 * @param window Referencja do obiektu klasy sf::RenderWindow reprezentuj¹cego okno aplikacji.
 */
	void render(sf::RenderWindow& window);
};

