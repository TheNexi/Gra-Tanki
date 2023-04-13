#include "Game.h"

// Funkcje prywatne
void Game::stworzZmienne()
{
	this->window = nullptr;
	
}

void Game::stworzOkno()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	


	this->window = new sf::RenderWindow(this->videoMode, "Gra Tanki", sf::Style::Close);
	

}
// Konstuktor 
Game::Game()
{
	this->stworzZmienne();
	this->stworzOkno();

}

// Destruktor
Game::~Game()
{
	delete this->window;

}

const bool Game::running() const
{
	return this->window->isOpen();
}


void Game::pollEvents()
{
    //Podczas otwartego okna
    while (this->window->pollEvent(this->ev))
    {
        //Zmiana dzialania
        switch (this->ev.type)
        {
            //zamykanie gry
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
            //zamykanie gry koniec

            //poruszanie sie obiektu


            //poruszanie sie obiektu koniec
        }
    }
}

//Funkcje
void Game::update()
{
	//Poruszanie obiektow

    this->pollEvents();

}

void Game::render()
{
    this->window->clear();

    //Tworzenie obiektow

    this->window->display();

}
