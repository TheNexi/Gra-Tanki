#include "Player.h"

using namespace std;

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
	this->movementSpeed = 1.f;
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



//Funkcje
void Player::move(const float dirX, const float dirY)
{
	//flexible, move to diferent directions
	
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);


}
void Player::update()
{


}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}
