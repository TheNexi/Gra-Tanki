#include "Player.h"

using namespace std;

void Player::stworzZmienne()
{
	this->movementSpeed = 1.85f;

}

void Player::initTexture()
{
	//Tekstury z pliku
	if (!this->texture.loadFromFile("Textures/Tank v2.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza"<<endl;
	}



}

void Player::initSprite()
{
	//Texture to sprite
	this->sprite.setTexture(this->texture);

	//Zmiana rozmiaru sprite
	//this->sprite.scale(0.5f, 0.5f);

}




Player::Player()
{
	this->stworzZmienne();
	this->initTexture();
	this->initSprite();
	this->sprite.setOrigin(25, 25);

}

Player::~Player()
{


}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);

}


//Funkcje
void Player::move(const float dirX, const float dirY)
{
	//poruszanie sie obiektu

	coord = this->sprite.getPosition();

	if (coord.x > 25 && coord.x < 775 && coord.y > 25 && coord.y < 575)
	{
		this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
	}
	else if (coord.y <= 25)
	{
		this->sprite.move(dirX, dirY + 1);

	}
	else if (coord.x >= 775)
	{
		this->sprite.move(dirX - 1, dirY);

	}
	else if (coord.y >= 575)
	{
		this->sprite.move(dirX, dirY - 1);


	}
	else if (coord.x <= 25)
	{
		this->sprite.move( dirX + 1, dirY);


	}

}

void Player::rotate_ob(float angle)
{
	if (angle != this->sprite.getRotation())
	{
		this->sprite.setRotation(angle);
	}
}

float Player::ob_rotation()
{
	return this->sprite.getRotation();
}


void Player::update()
{
	

}


void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}

void Player::color_change()
{
	if (!this->texture.loadFromFile("Textures/tank v3.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}
}