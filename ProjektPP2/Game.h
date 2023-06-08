#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Bricks.h"
#include "Flag.h"

#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;


class Game
{
private:
	//obiekt obslugujacy okno gry i zdarzenia
	sf::RenderWindow* window;
	bool endGame;
	sf::Event ev;


	//Zasoby gry
	map<string, sf::Texture*> textures;// mapa przechowuj¹ca tekstury 
	vector <Bullet*> bullets;//wektor przechowujacy pociski

	sf::Font font;

	sf::Text guiTextPlayer;
	sf::Text guiTextEnemy;
	sf::Text endGameText;

	//Obiekt cegly
	vector <Bricks*> bricks;
	vector <Player>enemies;

	sf::Time time;
	sf::Clock clock;



	//Obiekt gracza i przeciwnika
	Player* player;
	Player* enemy;
	Player* bot;


	Flag* orzel;


	//Prywatne funkcje
	void stworzZmienne();
	void stworzOkno();
	void stworzTekstury();
	void initFonts();
	void initGuiText();
	void updateGui();
	void m_left(Player* object);
	void m_right(Player* object);
	void m_up(Player* object);
	void m_down(Player* object);
	void logic_enemy(Player* object);

	void updateEnemies(Player* object);
	void stworzObiektGracz();
	void stworzObiektPrzeciwnik();

	void stworzCegly();

	void stworzFlage();


public:
	//Konstruktory / Destruktory
	Game();
	virtual ~Game();


	//Funkcje
	void run();
	void spawnEnemy();
	void destroy();
	void boom_sound();
	void updatePlayer(Player* any_player);
	void updateBricks(Player* object);

	void Brickscollisions(Player* object);
	void Playerscollisions(Player* object, Player* object1);
	void Playerscollisions(Player* object, Flag* object2);
	void updateBullets();
	void pollEvents();
	void updateEnemies();
	void renderEnemies();
	void bulletcollision(Player* object);
	void bulletcollision(Flag* object);
	void update();
	void renderGui(sf::RenderTarget* target);
	void render();

};
