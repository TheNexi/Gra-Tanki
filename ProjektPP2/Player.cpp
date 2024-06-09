/**
 * @file Player.cpp
 * @brief Plik zrodlowy klasy Player
 */

#include "Player.h"

using namespace std;
#include <string>
/**
 *@brief funkcja przypisujaca podstawowe parametry
 * 
 */
void Player::stworzZmienne()// m.in przypisanie predkosci poruszania sie 
{
	this->movementSpeed = 1.0f;
	this->bot_destroyed = false;
}
/**
 *@brief inicjacja tekstur czolgu
 *
 */
void Player::initTexture()
{
	//Wczytanie tekstury z pliku
	if (!this->texture.loadFromFile("Textures/Tank v2.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}



}
/**
 *@brief inicjacja tekstury do sprite 
 *
 */
void Player::initSprite()
{
	//inicjacja tekstury do obiektu typu sprite
	this->sprite.setTexture(this->texture);

}


/**
 *@brief funkcja przypisujaca klawisze do kontrolowania czolgu
 * 
 * @param left parametr do strzalki w lewo
 * @param right parametr do strzalki w prawo
 * @param up parametr do strzalki w gore
 * @param down parametr do strzalki w dol
 * @param shot parametr do strzelania
 */
void Player::setMovementControl(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key shot)
{
	this->left = left;
	this->right = right;
	this->up = up;
	this->down = down;
	this->shot = shot;
}

/**
 * @brief konstruktor wywolujace funkcje inicjuj¹ce.
 * 
 */
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
/**
 * @brief funkcja zwracajaca pozycje obiektu
 * 
 * @return zwrot obiektu typu Vector2f
 */
const sf::Vector2f& Player::getPos() const//funkcja zwracajaca pozycje obiektu
{
	return this->sprite.getPosition();
}
const sf::Vector2f Player::getCenter() const
{
	return this->sprite.getPosition() + 
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		); //œrodek obiektu
}
/** 
 * @brief funkcja zwracajaca krawedzie
 * 
 * @return obiekt typu Floatrect
 */
const sf::FloatRect Player::getBounds() const //funkcja zwracajaca krawedzie obiektu
{
	return this->sprite.getGlobalBounds();
}
/**
 * @brief funkcja ustawiajaca pozycje obiektu.
 * 
 * @param pos obiekt typu Vector2f zawieraj¹cy zadana pozycje
 */
void Player::setPosition(const sf::Vector2f pos)//ustawia pozycje poprzez wektor
{
	this->sprite.setPosition(pos);
}
/**
 * @brief przeciazona funkcja setPosition rowniez ustawiajaca pozycje jednak po dwoch zmiennych.
 * 
 * @param x ¿¹dany parametr osi X 
 * @param y ¿¹dany parametr osi Y
 */
void Player::setPosition(const float x, const float y)//ustawia pozycje poprzed dwie zmienne
{
	this->sprite.setPosition(x, y);

}


/**
 * @brief  funkcja przemieszczaj¹ca obiekt z uwzglednieniem granic mapy.
 * 
 * @param dirX wspolrzedna przemieszczenia na osi X 
 * @param dirY wspolrzedna przemieszczenia na osi Y
 */
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
/**
 * @brief funkcja obracaj¹ca obiekt o zadany k¹t.
 * 
 * @param angle zadany k¹t obrotu
 */
void Player::rotate_ob(float angle)//funkcja obracaj¹ca obiekt 
{
	if (angle != this->sprite.getRotation())
	{
		this->sprite.setRotation(angle);
	}
}
/**
 * @brief funkcja zwracaj¹ca jaki k¹t obrotu ma obiekt.
 * 
 * @return k¹t obrotu w stopniach 
 */
float Player::ob_rotation()//funkcja zwracajaca jaki k¹t ma obiekt
{
	return this->sprite.getRotation();
}


void Player::update()
{


}

/**
 * @brief funkcja renderuj¹ca obiekt.
 *
 * @param target okno w którym ma sie renderowaæ
 */
void Player::render(sf::RenderTarget& target)//funkcja renderujaca obiekt 
{
	target.draw(this->sprite);

}

/**
 * @brief przeci¹¿ona funkcja renderuj¹ca obiekt.
 * 
 * @param target okno w którym ma sie renderowaæ
 * @param shader 
 */
void Player::render(sf::RenderTarget& target, sf::Shader* shader)//funkcja renderujaca obiekt 
{
	shader->setUniform("hasTexture", true);
	shader->setUniform("lightPos", this->getCenter());

	target.draw(this->sprite, shader);
}

/**
 * @brief funkcja zmieniaj¹ca teksture obiektu.
 * 
 */
void Player::color_change()//funkcja do ustawienia tekstury obiektu
{
	if (!this->texture.loadFromFile("Textures/tank v2.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}
}
/**
 * @brief funkcja zmieniaj¹ca teksture obiektu komputera.
 *
 */
void Player::bot_texture()
{
	if (!this->texture.loadFromFile("Textures/tank v4.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki bota" << endl;
	}


}
/**
 * @brief funkcja zmieniaj¹ca teksture obiektu komputera na zniszczon¹.
 *
 */
void Player::destroyed_tank_bot()
{
	if (!this->texture.loadFromFile("Textures/tank_yellow_destroyed.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki bota zniszczone" << endl;
	}
}
/**
 * @brief funkcja resetuj¹ca teksture obiektu.
 *
 */
void Player::resetTexture()
{
	//Wczytanie tekstury z pliku
	if (!this->texture.loadFromFile("Textures/Tank v2.png"))
	{
		cout << "ERROR::PLAYER::Blad przy wczytywaniu grafiki obiektu gracza" << endl;
	}

}