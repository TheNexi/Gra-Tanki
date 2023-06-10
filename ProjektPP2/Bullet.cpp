/**
 * @file Bullet.cpp
 *
 * @brief Plik nag��wkowy klasy Bullet.
 */

#include "Bullet.h"

/**
 * @brief Konstruktor klasy Bullet.
 *
 * Tworzy obiekt pocisku o okre�lonych parametrach.
 *
 * @param texture Wska�nik do tekstury pocisku.
 * @param pos_x Wsp�rz�dna x pozycji pocisku.
 * @param pos_y Wsp�rz�dna y pozycji pocisku.
 * @param dir_x Kierunek ruchu pocisku w osi x.
 * @param dir_y Kierunek ruchu pocisku w osi y.
 * @param movement_speed Pr�dko�� poruszania si� pocisku.
 * @param p_name Nazwa pocisku.
 */
Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed,std::string p_name) //konstuktor klasy Bullet do tworzenia obiektu pocisku
{
	this->shape.setTexture(*texture); //tekstura obrazu pocisku /**< Ustawia tekstur� pocisku na podstawie przekazanego wska�nika do tekstury */

	this->shape.setPosition(pos_x, pos_y); //pozycja pocisku z przekazanych parametr�w /**< Ustawia pozycj� pocisku na podstawie przekazanych wsp�rz�dnych */
	this->direction.x = dir_x; //przypisanie kierunku x przekazanego przez parametr do wektora direction /**< Ustawia kierunek ruchu pocisku w osi x */
	this->direction.y = dir_y; //przypisanie kierunku y przekazanego przez parametr do wektora direction /**< Ustawia kierunek ruchu pocisku w osi y */
	this->movementSpeed = movement_speed; //predkosc pocisku z przekazanego parametru /**< Ustawia pr�dko�� poruszania si� pocisku na podstawie przekazanej warto�ci */
	this->p_name = p_name; /**< Ustawia nazw� pocisku na podstawie przekazanej warto�ci */
	std::cout << p_name << "\n"; /**< Wypisuje nazw� pocisku na standardowe wyj�cie */

}
/**
	 * @brief Destruktor klasy Bullet.
	 */
Bullet::~Bullet() //Destruktor
{

}
/**
	 * @brief Metoda zwracaj�ca granice obiektu pocisku.
	 *
	 * @return Granice obiektu pocisku w postaci prostok�ta.
	 */
const sf::FloatRect Bullet::getBounds() const //Metoda do granic obiektu(prostokatu)
{
	return this->shape.getGlobalBounds(); //Zwraca granice obiektu uwzgl�dniaj�c� pozycj� pocisku na ekranie
}
/**
 * @brief Metoda aktualizuj�ca pozycj� pocisku na ekranie.
 */
void Bullet::update()
{
	//Poruszanie pocisku
	this->shape.move(this->movementSpeed * this->direction); //Wektor przesuniecia pocisku odpowiadajacy predkosci i kierunku

}
/**
	 * @brief Metoda do rysowania pocisku na ekranie.
	 *
	 * @param target Wska�nik na obiekt RenderTarget, na kt�rym ma by� narysowany pocisk.
	 */
void Bullet::render(sf::RenderTarget* target) //Metoda do rysowania pocisku na ekranie
{
	target->draw(this->shape); //wywo�anie funkcji wyswietlajacej pocisk (target) na ekranie

}
