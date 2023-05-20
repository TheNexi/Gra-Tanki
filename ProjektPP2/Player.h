#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>



class Player
{
private:
	sf::Texture texture;//obiekt klasy texture z biblioteki sfml
	sf::Sprite sprite;//obiekt klasy sprite z biblioteki sfml

	float movementSpeed;
	sf::Vector2f coord;//obiekt klasy Vector2f z biblioteki sfml

	

	//Funkcje prywatne
	void stworzZmienne();
	void initTexture();
	void initSprite();
	

public:
	Player();
	virtual ~Player();
	int hp = 10;
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


	void rotate_ob(float angle);
	void update();
	void render(sf::RenderTarget& target);
	void color_change();

	float ob_rotation();

};

