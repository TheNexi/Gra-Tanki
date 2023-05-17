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
	
	sf::Time time;
	sf::Clock clock;



	//Obiekt gracza i przeciwnika
	Player* player;
	Player* enemy;
	
	//Obiekt cegly
	Bricks* bricks;

	
	//Prywatne funkcje
	void stworzZmienne();
	void stworzOkno();
	void stworzTekstury();

	void stworzObiektGracz();
	void stworzObiektPrzeciwnik();
	void initBricks();

public:
	//Konstruktory / Destruktory
	Game();
	virtual ~Game();


	//Funkcje
	void run();
	void spawnEnemy();


	void updatePlayer(Player* any_player);
	void updateBullets();
	void pollEvents();
	void updateEnemies();
	void renderEnemies();

	void update();
	void render();

};
