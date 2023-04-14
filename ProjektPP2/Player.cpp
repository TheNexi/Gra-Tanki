#include "Player.h"

using namespace std;

void Player::stworzZmienne()
{
	this->movementSpeed = 1.85f;
	this->attackCooldownMax = 40.f;
	this->attackCooldown = this->attackCooldownMax;

}

void Player::initTexture()
{
	//Tekstury z pliku
	if (!this->texture.loadFromFile("Textures/Tank_player.png"))
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
	//flexible, move to diferent directions
	
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);


}
const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}
void Player::updateAttack()
{
	if(this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;


}
void Player::update()
{
	this->updateAttack();

}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}
