/**
 * @file Bricks.cpp
 * @brief Plik Ÿród³owy klasy Bricks
 */
#include "Bricks.h"
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
/**
 * @brief Konstruktor klasy Bricks.
 * Inicjalizuje obiekt ceg³y z przekazanymi parametrami.
 *
 * @param texture WskaŸnik do tekstury ceg³y.
 * @param pos_x Wspó³rzêdna x pozycji ceg³y.
 * @param pos_y Wspó³rzêdna y pozycji ceg³y.
 * @param destructionHp Punkty zniszczenia ceg³y.
 */
Bricks::Bricks(sf::Texture* texture,float pos_x, float pos_y, float destructionHp)
{
	this->shape.setTexture(*texture); //tekstura obrazu pocisku
	
	//this->shape.setOrigin(25, 25);
	this->shape.setPosition(pos_x, pos_y); // ustawienie pozycji cegly na ekranie
}
/**
 * @brief Destruktor klasy Bricks.
 * Nie s¹ podejmowane ¿adne dzia³ania specyficzne dla destruktora klasy Bricks.
 */
Bricks::~Bricks()
{

}

/**
 * @brief Metoda zwracaj¹ca granice ceg³y.
 * @return Obiekt klasy sf::FloatRect reprezentuj¹cy granice ceg³y.
 */
const sf::FloatRect Bricks::getBounds() const
{
	return this->shape.getGlobalBounds(); //Zwraca granice obiektu uwzglêdniaj¹c¹ pozycjê pocisku na ekranie
}

/**
 * @brief Metoda aktualizuj¹ca stan ceg³y.
 * Nie s¹ podejmowane ¿adne dzia³ania w metodzie update().
 */
void Bricks::update()
{

}

/**
 * @brief Metoda renderuj¹ca ceg³ê na oknie.
 * @param window Referencja do obiektu klasy sf::RenderWindow, reprezentuj¹cego okno aplikacji.
 */
void Bricks::render(sf::RenderWindow& window)
{
	window.draw(shape); // Wyœwietlanie ceg³y na ekranie
}
