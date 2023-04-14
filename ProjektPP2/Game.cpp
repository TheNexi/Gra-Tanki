#include "Game.h"

using namespace std;

// Funkcje prywatne
void Game::stworzZmienne()
{
	this->window = nullptr;
}

void Game::stworzOkno()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800,600), "Gra Tanki", sf::Style::Close ); 
    // TitleBar
	
    this->window->setFramerateLimit(144); //hatch screen
    this->window->setVerticalSyncEnabled(false); //wy³¹czenie synchorizacji pionowej
     
}
void Game::stworzTekstury()
{
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

}
void Game::stworzObiektGracz()
{
    this->player = new Player();

}
void Game::stworzObiektPrzeciwnik()
{

}
// Konstuktor 
Game::Game()
{
	this->stworzZmienne();
	this->stworzOkno();
    this->stworzTekstury();
    this->stworzObiektGracz();
    this->stworzObiektPrzeciwnik();
}

// Destruktor
Game::~Game()
{
	delete this->window;
    delete this->player;

    //usuwanie tekstur (mapa)

    for (auto& i : this->textures)
    {
        delete i.second;
    }

    for (auto* i : this->bullets)
    {
        delete i; // usuwa dynamiczna pamiec w wektorze
    }
}


void Game::run()
{
    while(this->window->isOpen())
    { 
        this->update();
        this->render();
    }

}

//Funkcje
void Game::spawnEnemy()
{
    
    
}

void Game::updateCollision()
{
    //KOLIZJE z plansza
    //lewa strona ekranu gry
    if (this->player->getBounds().left < 0.f)
    {
        this->player->setPosition(0.f, this->player->getBounds().top);
    }
    //prawa strona ekranu gry (nie moga byc jednoczesnie lewa i prawa)
    else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
    {
        this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
    }

    //gora ekranu gry
    if (this->player->getBounds().top < 0.f)
    {
        this->player->setPosition(this->player->getBounds().left, 0.f);
    }

    //dolna granica ekranu gry
    else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
    {
        this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
    }
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

   
        }
    }
}

void Game::updateEnemies()
{
    
}

void Game::updatePlayer()
{
    //Poruszanie obiektu gracza
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        this->player->move(-1.f, 0.f);
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->player->move(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->player->move(0.f, -1.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->player->move(0.f, 1.f);
    }
    //Poruszanie obiektu gracza koniec

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack() )
    {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 25, this->player->getPos().y, 0.f, -1.f, 2.f));
    }

    
}

void Game::updateBullets()
{
    unsigned int licznik = 0;
    for (auto* bullet : this->bullets)
    {
        bullet->update();

        //pozycja pocisku do okna gry
        
        //góra ekranu
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--;

            cout << "Pociski: " << this->bullets.size() << endl;
        }

        licznik++;
    }

}


void Game::update()
{
    this->pollEvents();

    

    this->updatePlayer();

    this->updateCollision();

    this->updateBullets();
    this->player->update();

    this->updateEnemies();

}

void Game::renderEnemies()
{

}

void Game::render()
{
    this->window->clear();

 
    this->renderEnemies();
    this->player->render(*this->window);
    
    for (auto* bullet : this->bullets)
    {
        bullet->render(this->window);
    }

    this->window->display();

}
