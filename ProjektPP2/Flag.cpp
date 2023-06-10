/**
 * @file Flag.cpp
 *
 * @brief Plik nag��wkowy klasy Flag.
 */

#include "Flag.h"
 /**
	  * @brief Inicjalizuje tekstur� flagi.
	  *
	  * �aduje tekstur� z pliku "Textures/flag1.jpg" i przypisuje j� do zmiennej texture.
	  * W przypadku b��du podczas wczytywania wy�wietla odpowiednie komunikaty.
	  */
void Flag::initTexture()
{
	if (!this->texture.loadFromFile("Textures/flag1.jpg"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki flagi" << endl;
	}
}
/**
	 * @brief Inicjalizuje sprite flagi.
	 *
	 * Ustawia tekstur� sprite'a na wcze�niej zainicjalizowan� tekstur�.
	 */
void Flag::initSprite()
{
	//inicjacja tekstury do obiektu typu sprite
	this->sprite.setTexture(this->texture);

}
/**
	 * @brief Konstruktor klasy Flag.
	 *
	 * Inicjalizuje tekstur� i sprite flagi poprzez wywo�anie funkcji initTexture() i initSprite().
	 */
Flag::Flag()
{
	this->initTexture();
	this->initSprite();
}
/**
	 * @brief Destruktor klasy Flag.
	 */
Flag::~Flag()
{

}
/**
	 * @brief Ustawia pozycj� flagi.
	 *
	 * @param x Wsp�rz�dna x pozycji flagi.
	 * @param y Wsp�rz�dna y pozycji flagi.
	 */
void Flag::setPosition(const float x, const float y)//ustawia pozycje poprzed dwie zmienne
{
	this->sprite.setPosition(x, y);

}
/**
	 * @brief Zwraca granice flagi.
	 *
	 * @return Granice flagi uwzgl�dniaj�ce jej pozycj� na ekranie.
	 */
const sf::FloatRect Flag::getBounds() const
{
	return this->sprite.getGlobalBounds(); //Zwraca granice obiektu uwzgl�dniaj�c� pozycj� pocisku na ekranie
}
/**
	 * @brief Wy�wietla flag� na ekranie.
	 *
	 * @param window Referencja do okna renderowania, na kt�rym ma by� wy�wietlona flaga.
	 */
void Flag::render(sf::RenderWindow& window)
{
	window.draw(sprite); // Wy�wietlanie ceg�y na ekranie
}
