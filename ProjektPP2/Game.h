#pragma once

/**
*
*@file Game.h
*@brief Plik naglowkowy klasy Game
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
 * @brief Glowna klasa reprezentujaca logike gry.
 *
 * Klasa Game zawiera wszystkie niezbedne metody i pola, aby zarzadzac logika gry.
 * Odpowiada za inicjalizacje, aktualizacje i renderowanie elementow gry.
 * Wykorzystuje klasy Player, Bullet, Bricks, Flag, Menu oraz zewnetrzne biblioteki takie jak SFML.
 */

class Game
{
private:
	//obiekt obslugujacy okno gry i zdarzenia
	sf::RenderWindow* window;
	sf::Event ev;

	//Zmienne prywatne s³u¿¹ce jako flagi do obs³ugi menu
	bool endGame;
	bool returnToMenu;
	bool menuRendered;
	int selectedMenuOption;
	

	//Zasoby gry
	map<string, sf::Texture*> textures;// mapa przechowuj¹ca tekstury 
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

	//Obiekty do obs³ugi czasu
	sf::Time time;
	sf::Time spawnTime;
	sf::Clock clock;
	sf::Clock spawnclock;



	//Obiekt gracza i przeciwnika
	Player* player;
	Player* enemy;

	//Obiekt flagi
	Flag* orzel;

	//elementy dzwiekowe
	sf::SoundBuffer shotSoundBuffer;
	sf::Sound shotSound;
	sf::SoundBuffer backgroundBuffer;
	sf::Sound backgroundMusic;

	//Prywatne funkcje
	void stworzZmienne();
	void stworzOkno();
	void stworzTekstury();
	void initFonts();
	void initGuiText();
	void initSound();
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

		// Inne zmienne prywatne
		sf::RenderTexture fogTexture;
		sf::Sprite fogSprite;
		sf::CircleShape visionCircle;
		void initFogOfWar();
		sf::Shader fogShader;
	
		sf::Texture backgroundTexture;
		sf::Sprite backgroundImage;
		void initBackgroundImage();


public:
	// Konstruktor
	Game();
	// Destruktor
	virtual ~Game();
	void updateFogOfWar();
	//Zmienna do obs³ugi trybu gry
	bool playervsbot;
	float bot_x=25,bot_y=25;
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
	void renderBackground();
	void resetGame();
	
};
