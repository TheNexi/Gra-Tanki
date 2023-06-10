#pragma once

/**
*
*@file Game.h
*@brief Plik nag��wkowy klasy Game
*/

#include "Player.h"
#include "Bullet.h"
#include "Bricks.h"
#include "Flag.h"
#include "Menu.h"

#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>


using namespace std;


/**
 * @class Game
 * @brief G��wna klasa reprezentuj�ca logik� gry.
 *
 * Klasa Game zawiera wszystkie niezb�dne metody i pola, aby zarz�dza� logik� gry.
 * Odpowiada za inicjalizacj�, aktualizacj� i renderowanie element�w gry.
 * Wykorzystuje klasy Player, Bullet, Bricks, Flag, Menu oraz zewn�trzne biblioteki takie jak SFML.
 */

class Game
{
private:
	//obiekt obslugujacy okno gry i zdarzenia
	sf::RenderWindow* window;
	sf::Event ev;

	//Zmienne prywatne s�u��ce jako flagi do obs�ugi menu
	bool endGame;
	bool returnToMenu;
	bool menuRendered;
	int selectedMenuOption;
	

	//Zasoby gry
	map<string, sf::Texture*> textures;// mapa przechowuj�ca tekstury 
	vector <Bullet*> bullets;//wektor przechowujacy pociski
	vector <Player*> enemies;


	//Obiekty do interfejsu graficznego
	sf::Font font;
	sf::Text guiTextPlayer;
	sf::Text guiTextEnemy;
	sf::Text guiTextBots;
	sf::Text guiTextFlag;
	sf::Text endGameText;

	//Obiekt cegly
	vector <Bricks*> bricks;

	//Obiekty do obs�ugi czasu
	sf::Time time;
	sf::Time spawnTime;
	sf::Clock clock;
	sf::Clock spawnclock;



	//Obiekt gracza i przeciwnika
	Player* player;
	Player* enemy;

	//Obiekt flagi
	Flag* orzel;


	//Prywatne funkcje
	void stworzZmienne();
	void stworzOkno();
	void stworzTekstury();
	void initFonts();
	void initGuiText();
	void updateGui();
	void updateGuiVsBots();
	void m_left(Player* object);
	void m_right(Player* object);
	void m_up(Player* object);
	void m_down(Player* object);
	void logic_enemy(Player* object);
	void updateEnemies(Player* object);
	void updateAllEnemies();
	void stworzObiektGracz();
	void stworzObiektPrzeciwnik();
	void stworzCegly();
	void stworzFlage();

public:
	// Konstruktor
	Game();
	// Destruktor
	virtual ~Game();

	//Zmienna do obs�ugi trybu gry
	bool playervsbot;
	float bot_x=10,bot_y=10;
	int createdEnemies=0;
	// Funkcje
	void run();
	void renderMenu();
	bool shouldReturnToMenu();
	void spawnEnemy();
	void updatePlayer(Player* any_player);
	void updateBricks(Player* object);
	void Brickscollisions(Player* object);
	void Playerscollisions(Player* object, Player* object1);
	void Playerscollisions(Player* object, Flag* object2);
	void updateBullets();
	void pollEvents();
	void renderEnemies();
	void bulletcollision(Player* object);
	void bulletcollision(Flag* object);
	void bulletcollisionSi(Player* object, Player* object2);
	void bulletcollisionVsSi(Player* object, Player* object2);
	void bulletcollisionVsEnemy(Player* object, Player* object2);
	void update();
	void renderGui(sf::RenderTarget* target);
	void renderGuiBots(sf::RenderTarget* target);
	void render();
	void resetGame();
	
};
