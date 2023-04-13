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
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//
	const sf::Vector2f& getPos() const;

	//Funkcje
	void move(const float dirX, const float dirY);

	void update();
	void render(sf::RenderTarget& target);


};

