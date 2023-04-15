#include "Player.h"

using namespace std;

void Player::stworzZmienne()// m.in przypisanie predkosci poruszania sie 
{
	this->movementSpeed = 1.0f;

}

void Player::initTexture()
{
	//Wczytanie tekstury z pliku
	if (!this->texture.loadFromFile("Textures/Tank v2.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}



}

void Player::initSprite()
{
	//inicjacja tekstury do obiektu typu sprite
	this->sprite.setTexture(this->texture);

}




Player::Player()
{//konstruktor wywolujacy funkcje inicjujace
	this->stworzZmienne();
	this->initTexture();
	this->initSprite();
	this->sprite.setOrigin(25, 25);

}

Player::~Player()
{


}

const sf::Vector2f& Player::getPos() const//funkcja zwracajaca pozycje obiektu
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const //funkcja zwracajaca krawedzie obiektu
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const sf::Vector2f pos)//ustawia pozycje poprzez wektor
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)//ustawia pozycje poprzed dwie zmienne
{
	this->sprite.setPosition(x, y);

}


//Funkcje
void Player::move(const float dirX, const float dirY)//funkcja przemieszczająca obiekt z uwzględnieniem granic mapy
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

		this->sprite.move(dirX + 1, dirY);

	}

}

void Player::rotate_ob(float angle)//funkcja obracająca obiekt 
{
	if (angle != this->sprite.getRotation())
	{
		this->sprite.setRotation(angle);
	}
}

float Player::ob_rotation()//funkcja zwracajaca jaki kąt ma obiekt
{
	return this->sprite.getRotation();
}


void Player::update()
{


}


void Player::render(sf::RenderTarget& target)//funkcja renderujaca obiekt 
{
	target.draw(this->sprite);

}

void Player::color_change()//funkcja zmieniająca kolor tekstu obiektu
{
	if (!this->texture.loadFromFile("Textures/tank v3.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}
}