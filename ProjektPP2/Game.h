#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Bricks.h"

#include <map>
#include <vector>


using namespace std;


class Game
{
private:
	//obiekt obslugujacy okno gry i zdarzenia
	sf::RenderWindow* window;
	sf::Event ev;

	//Zasoby gry
	map<string, sf::Texture*> textures;// mapa przechowuj¹ca tekstury 
	vector <Bullet*> bullets;//wektor przechowujacy pociski
	
	//Obiekt cegly
	vector <Bricks*> bricks;


	sf::Time time;
	sf::Clock clock;



	//Obiekt gracza i przeciwnika
	Player* player;
	Player* enemy;
	
	

	
	//Prywatne funkcje
	void stworzZmienne();
	void stworzOkno();
	void stworzTekstury();

	void stworzObiektGracz();
	void stworzObiektPrzeciwnik();

	void stworzCegly();
	

public:
	//Konstruktory / Destruktory
	Game();
	virtual ~Game();


	//Funkcje
	void run();
	void spawnEnemy();
	void destroy();

	void updatePlayer(Player* any_player);
	void updateBricks();
	void Brickscollisions(Player* object);
	void Playerscollisions(Player* object, Player* object1);
	void updateBullets();
	void pollEvents();
	void updateEnemies();
	void renderEnemies();
	void bulletcollision(Player* object);
	void update();
	void render();

};
