#include "Game.h"

using namespace std;

// Funkcje prywatne
void Game::stworzZmienne()
{
	this->window = nullptr;

    //Logika gry
    this->points = 0;
    this->enemySpawnTimerMax = 1000.f;
    //this->enemySpawnTimer = 0;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
	
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
    //Obiekt jako kwadrat
    this->enemy.setPosition(10.f, 10.f);
    
    //enemy.setFillColor - zmiana koloru po trafieniu pociskiem
    //setScale -1 - to flip object
    this->enemy.setSize(sf::Vector2f(100.f, 100.f)); // 100x100 float
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f)); // objekt w skali x0.5
    this->enemy.setFillColor(sf::Color::Red);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);




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
    //random position, random color, add enemy to vector

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
        /*static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))*/
    );

    this->enemy.setFillColor(sf::Color::Green);

    //spawn enemy
    this->enemies.push_back(this->enemy);

    //usuwanie gdy sa na koncu ekranu
    
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
    //Updates the enemy spawn timer and spawns enemies when the total amount of enemies is smaller than the maximum
    //moves enemies downwards
    //removes the enemies at the edge of the screen
    if(this->enemies.size() < this->maxEnemies)
    { 
    if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
    { 
        //Spawn enemy and reset timer
        this->spawnEnemy();
        this->enemySpawnTimer = 0.f; // reset
    }
    else
        this->enemySpawnTimer += 1.f; // zwiekszanie
    }

    //Move the enemies

    for (auto& e : this->enemies)
    {
        e.move(0.f, 5.f);
    }


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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y, 1.f, -1.f, 0.5f));
    }


}

void Game::updateBullets()
{
    for (auto* bullet : this->bullets)
    {
        bullet->update();
    }

}


void Game::update()
{
    this->pollEvents();

    

    this->updatePlayer();
    this->updateBullets();

    this->updateEnemies();

}

void Game::renderEnemies()
{
    //render all the enemies
    for (auto& e : this->enemies)
    {
        this->window->draw(e);
    }


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
