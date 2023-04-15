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
<<<<<<< HEAD
	
	//Obiekt przeciwnika kwadrat

	
	
=======

	//Obiekt przeciwnika kwadrat



>>>>>>> cc9a0d988c8c71f83749bd6bb7a5b71d2bd5b614
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
