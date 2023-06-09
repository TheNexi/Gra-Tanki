#include "Player.h"

using namespace std;
#include <string>

void Player::stworzZmienne()// m.in przypisanie predkosci poruszania sie 
{
	this->movementSpeed = 1.0f;
	this->bot_destroyed = false;
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



void Player::setMovementControl(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key shot)
{
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
	this->shot = shot;
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
void Player::move(const float dirX, const float dirY)//funkcja przemieszczaj¹ca obiekt z uwzglêdnieniem granic mapy
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

void Player::rotate_ob(float angle)//funkcja obracaj¹ca obiekt 
{
	if (angle != this->sprite.getRotation())
	{
		this->sprite.setRotation(angle);
	}
}

float Player::ob_rotation()//funkcja zwracajaca jaki k¹t ma obiekt
{
	return this->sprite.getRotation();
}


void Player::update()
{


}


void Player::render(sf::RenderTarget& target)//funkcja renderujaca obiekt 
{
	if(this->hp>0)
	target.draw(this->sprite);

}
void Player::delete_object()
{
	delete this;
}

void Player::color_change()//funkcja do ustawienia tekstury obiektu
{
	if (!this->texture.loadFromFile("Textures/tank v3.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}
}

void Player::bot_texture()
{
	if (!this->texture.loadFromFile("Textures/tank v4.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki bota" << endl;
	}


}

void Player::destroyed_tank_bot()
{
	if (!this->texture.loadFromFile("Textures/tank_yellow_destroyed.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki bota zniszczone" << endl;
	}
}
