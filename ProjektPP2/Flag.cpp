/**
 * @file Flag.cpp
 *
 * @brief Plik nag³ówkowy klasy Flag.
 */

#include "Flag.h"
 /**
	  * @brief Inicjalizuje teksturê flagi.
	  *
	  * £aduje teksturê z pliku "Textures/flag1.jpg" i przypisuje j¹ do zmiennej texture.
	  * W przypadku b³êdu podczas wczytywania wyœwietla odpowiednie komunikaty.
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
	 * Ustawia teksturê sprite'a na wczeœniej zainicjalizowan¹ teksturê.
	 */
void Flag::initSprite()
{
	//inicjacja tekstury do obiektu typu sprite
	this->sprite.setTexture(this->texture);

}
/**
	 * @brief Konstruktor klasy Flag.
	 *
	 * Inicjalizuje teksturê i sprite flagi poprzez wywo³anie funkcji initTexture() i initSprite().
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
	 * @brief Ustawia pozycjê flagi.
	 *
	 * @param x Wspó³rzêdna x pozycji flagi.
	 * @param y Wspó³rzêdna y pozycji flagi.
	 */
void Flag::setPosition(const float x, const float y)//ustawia pozycje poprzed dwie zmienne
{
	this->sprite.setPosition(x, y);

}
/**
	 * @brief Zwraca granice flagi.
	 *
	 * @return Granice flagi uwzglêdniaj¹ce jej pozycjê na ekranie.
	 */
const sf::FloatRect Flag::getBounds() const
{
	return this->sprite.getGlobalBounds(); //Zwraca granice obiektu uwzglêdniaj¹c¹ pozycjê pocisku na ekranie
}
/**
	 * @brief Wyœwietla flagê na ekranie.
	 *
	 * @param window Referencja do okna renderowania, na którym ma byæ wyœwietlona flaga.
	 */
void Flag::render(sf::RenderWindow& window)
{
	window.draw(sprite); // Wyœwietlanie ceg³y na ekranie
}
