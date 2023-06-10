/**
 * @file Bricks.cpp
 * @brief Plik �r�d�owy klasy Bricks
 */
#include "Bricks.h"
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>
/**
 * @brief Konstruktor klasy Bricks.
 * Inicjalizuje obiekt ceg�y z przekazanymi parametrami.
 *
 * @param texture Wska�nik do tekstury ceg�y.
 * @param pos_x Wsp�rz�dna x pozycji ceg�y.
 * @param pos_y Wsp�rz�dna y pozycji ceg�y.
 * @param destructionHp Punkty zniszczenia ceg�y.
 */
Bricks::Bricks(sf::Texture* texture,float pos_x, float pos_y, float destructionHp)
{
	this->shape.setTexture(*texture); //tekstura obrazu pocisku
	
	//this->shape.setOrigin(25, 25);
	this->shape.setPosition(pos_x, pos_y); // ustawienie pozycji cegly na ekranie
}
/**
 * @brief Destruktor klasy Bricks.
 * Nie s� podejmowane �adne dzia�ania specyficzne dla destruktora klasy Bricks.
 */
Bricks::~Bricks()
{

}

/**
 * @brief Metoda zwracaj�ca granice ceg�y.
 * @return Obiekt klasy sf::FloatRect reprezentuj�cy granice ceg�y.
 */
const sf::FloatRect Bricks::getBounds() const
{
	return this->shape.getGlobalBounds(); //Zwraca granice obiektu uwzgl�dniaj�c� pozycj� pocisku na ekranie
}

/**
 * @brief Metoda aktualizuj�ca stan ceg�y.
 * Nie s� podejmowane �adne dzia�ania w metodzie update().
 */
void Bricks::update()
{

}

/**
 * @brief Metoda renderuj�ca ceg�� na oknie.
 * @param window Referencja do obiektu klasy sf::RenderWindow, reprezentuj�cego okno aplikacji.
 */
void Bricks::render(sf::RenderWindow& window)
{
	window.draw(shape); // Wy�wietlanie ceg�y na ekranie
}
