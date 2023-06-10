/**
 * @file Bullet.cpp
 *
 * @brief Plik zrodlowy klasy Bullet.
 */

#include "Bullet.h"

/**
 * @brief Konstruktor klasy Bullet.
 *
 * Tworzy obiekt pocisku o okreœlonych parametrach.
 *
 * @param texture Wskaznik do tekstury pocisku.
 * @param pos_x Wspolrzêdna x pozycji pocisku.
 * @param pos_y Wspolrzedna y pozycji pocisku.
 * @param dir_x Kierunek ruchu pocisku w osi x.
 * @param dir_y Kierunek ruchu pocisku w osi y.
 * @param movement_speed Predkosc poruszania siê pocisku.
 * @param p_name Nazwa gracza przypisanego do danego pocisku.
 */
Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,std::string p_name) //konstuktor klasy Bullet do tworzenia obiektu pocisku
{
	this->shape.setTexture(*texture); //tekstura obrazu pocisku /**< Ustawia teksturê pocisku na podstawie przekazanego wskaŸnika do tekstury */

	this->shape.setPosition(pos_x, pos_y); //pozycja pocisku z przekazanych parametrów /**< Ustawia pozycjê pocisku na podstawie przekazanych wspó³rzêdnych */
	this->direction.x = dir_x; //przypisanie kierunku x przekazanego przez parametr do wektora direction /**< Ustawia kierunek ruchu pocisku w osi x */
	this->direction.y = dir_y; //przypisanie kierunku y przekazanego przez parametr do wektora direction /**< Ustawia kierunek ruchu pocisku w osi y */
	this->movementSpeed = movement_speed; //predkosc pocisku z przekazanego parametru /**< Ustawia prêdkoœæ poruszania siê pocisku na podstawie przekazanej wartoœci */
	this->p_name = p_name; /**< Ustawia nazwê pocisku na podstawie przekazanej wartoœci */
	std::cout << p_name << "\n"; /**< Wypisuje nazwê pocisku na standardowe wyjœcie */

}
/**
	 * @brief Destruktor klasy Bullet.
	 */
Bullet::~Bullet() //Destruktor
{

}
/**
	 * @brief Metoda zwracajaca granice obiektu pocisku.
	 *
	 * @return Granice obiektu pocisku w postaci prostokata.
	 */
const sf::FloatRect Bullet::getBounds() const //Metoda do granic obiektu(prostokatu)
{
	return this->shape.getGlobalBounds(); //Zwraca granice obiektu uwzglêdniaj¹c¹ pozycjê pocisku na ekranie
}
/**
 * @brief Metoda aktualizujaca pozycje pocisku na ekranie.
 */
void Bullet::update()
{
	//Poruszanie pocisku
	this->shape.move(this->movementSpeed * this->direction); //Wektor przesuniecia pocisku odpowiadajacy predkosci i kierunku

}
/**
	 * @brief Metoda do rysowania pocisku na ekranie.
	 *
	 * @param target Wskaznik na obiekt RenderTarget, na którym ma byc narysowany pocisk.
	 */
void Bullet::render(sf::RenderTarget* target) //Metoda do rysowania pocisku na ekranie
{
	target->draw(this->shape); //wywo³anie funkcji wyswietlajacej pocisk (target) na ekranie

}
