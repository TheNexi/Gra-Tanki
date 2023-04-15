#pragma once
#include "Player.h"
#include "Bullet.h"

#include <map>
#include <vector>


using namespace std;


class Game
{
private:
	//Okno gry
	sf::RenderWindow* window;
	sf::Event ev;

	//Zasoby gry
	map<string, sf::Texture*> textures;
	vector <Bullet*> bullets;

	sf::Time time;
	sf::Clock clock;



	//Obiekt gracza
	Player* player;
	Player* enemy;

	//Obiekt przeciwnika kwadrat



	//Prywatne funkcje
	void stworzZmienne();
	void stworzOkno();
	void stworzTekstury();

	void stworzObiektGracz();
	void stworzObiektPrzeciwnik();

public:
	//Konstruktory / Destruktory
	Game();
	virtual ~Game();


	//Funkcje
	void run();
	void spawnEnemy();


	void updatePlayer();
	void updateBullets();
	void pollEvents();
	void updateEnemies();

	void update();

	void renderEnemies();
	void render();

};
