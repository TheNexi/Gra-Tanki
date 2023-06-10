/**
 * @file Player.h
 * @brief Plik naglowkowy klasy Player
 */

#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



 /**
* @brief Klasa reprezentuj�ca gracza w grze.
*
* Klasa `Player` zawiera wszystkie sk�adowe i metody zwi�zane z graczem w grze.
* Pozwala na sterowanie graczem, okre�lanie jego pozycji, obliczanie granic, manipulowanie
* parametrami takimi jak punkty �ycia, liczba zdobytych punkt�w, liczba zniszczonych przeciwnik�w
* oraz sterowanie ruchem i akcjami gracza. Gracz mo�e by� renderowany na ekranie gry i podlega�
* r�nym modyfikacjom, takim jak zmiana koloru czy tekstury. Klasa `Player` posiada r�wnie�
* funkcje pomocnicze do inicjalizacji wewn�trznych zmiennych i manipulacji obiektami graficznymi.
*/
class Player
{
private:
	sf::Texture texture;//obiekt klasy texture z biblioteki sfml
	sf::Sprite sprite;//obiekt klasy sprite z biblioteki sfml
	
	
	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml

	

	//Funkcje prywatne
	void stworzZmienne();
	void initTexture();
	void initSprite();
	

public:
	Player();
	virtual ~Player();
	float movementSpeed = 5.0;
	int hp=10;
	int points=0;
	bool bot_destroyed;
	int destroyedEnemies = 0;
	int numberOfEnemies = 5;

	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key shot;

	//Metody do okreslania pozycji obiektu
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	//Modyfikatory do kolizji
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	//Funkcje
	void move(const float dirX, const float dirY);
	void setMovementControl(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key shot);
	//sf::Keyboard::Key getKeyControl(string key);

	void delete_object();
	void rotate_ob(float angle);
	void update();
	void render(sf::RenderTarget& target);
	void color_change();
	void bot_texture();
	void destroyed_tank_bot();

	float ob_rotation();
	void resetTexture();
};

