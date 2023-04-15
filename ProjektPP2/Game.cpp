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
    
    this->player->setPosition(300.f, 450.f);
    
   
}
void Game::stworzObiektPrzeciwnik()
{
    this->enemy = new Player();
    this->enemy->setPosition(500, 550);
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
        this->player->rotate_ob(270);
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        this->player->move(1.f, 0.f);
        this->player->rotate_ob(90);
        
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        this->player->move(0.f, -1.f);
        this->player->rotate_ob(0);
        
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->player->move(0.f, 1.f);
        this->player->rotate_ob(180);
        
    }
    //Poruszanie obiektu gracza koniec

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {


        time = clock.getElapsedTime();
        //opoznienie miedzy strzalami
        if (time.asSeconds() > 0.5)
        {
            int angle = (int)this->player->ob_rotation();
            switch (angle)
            {
            case(0):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y - 25, 0.f, -1.f, 0.5f));
                clock.restart();
                break;
            }
            case(90):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 25, this->player->getPos().y, 1.f, 0.f, 0.5f));
                clock.restart();
                break;
            }
            case(180):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y + 25, 0.f, 1.f, 0.5f));
                clock.restart();
                break;
            }
            case(270):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x - 25, this->player->getPos().y, -1.f, 0.f, 0.5f));
                clock.restart();
                break;
            }

            }
        }
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

            cout << "Pocisk gora: " << this->bullets.size() << endl;
        }
        
        //lewa strona ekranu
        else if (bullet->getBounds().left + bullet->getBounds().width < 0.f)
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--;

            cout << "Pocisk lewa: " << this->bullets.size() << endl;
        }

        //prawa strona ekranu
        else if (bullet->getBounds().left > this->window->getSize().x)
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--;

            cout << "Pocisk prawa: " << this->bullets.size() << endl;
        }

        //dol ekranu
        else if (bullet->getBounds().top > this->window->getSize().y)
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--;

            cout << "Pocisk dol: " << this->bullets.size() << endl;
        }
        
        licznik++;
    }

}


void Game::update()
{
    this->pollEvents();

    this->updatePlayer();


    this->updateBullets();
    this->player->update();

    this->updateEnemies();

}

void Game::renderEnemies()
{
    this->enemy->render(*this->window);
    enemy->color_change();
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
