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
	sf::Texture texture;
	sf::Sprite sprite;
	
	float movementSpeed;



	//Funkcje prywatne
	void stworzZmienne();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	//Modyfikatory do kolizji
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);

	//Funkcje
	void move(const float dirX, const float dirY);

	
	void rotate_ob(float angle);
	void update();
	void render(sf::RenderTarget& target);

	float ob_rotation();

};

