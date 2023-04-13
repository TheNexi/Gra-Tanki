#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Game
{
private:
	//Zmienne
	//Okno gry
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	
	
	
	
	//Prywatne funkcje

	void stworzZmienne();
	void stworzOkno();

public:
	//Konstruktory / Destruktory
	Game();
	virtual ~Game();

	const bool running() const;


	//Funkcje
	void pollEvents();
	void update();
	void render();

};
