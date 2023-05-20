#include "Game.h"


using namespace std;

//Metody prywatne
void Game::stworzZmienne()
{
    this->window = nullptr; //Inicjalizacja pola window na pusty wska�nik
}

void Game::stworzOkno() //Metoda do tworzenia okna gry
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gra Tanki", sf::Style::Close); //Utworzenie nowego obiektu klasy RenderWindow
    

    this->window->setFramerateLimit(144); //Limit klatek na sekunde
    this->window->setVerticalSyncEnabled(false); //wy��czenie synchorizacji pionowej

}
void Game::stworzTekstury() //Metoda do za�adowania tekstur z pliku
{
    this->textures["BULLET"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BULLET"]->loadFromFile("Textures/bullet2.png"); //�adowanie tekstury pocisku z pliku

    this->textures["BRICKS"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BRICKS"]->loadFromFile("Textures/cegla.png"); //�adowanie tekstury pocisku z pliku
    
}
void Game::stworzObiektGracz() //Metoda do tworzenia obiektu gracza
{
    this->player = new Player(); //Utworzenie obiektu gracza
    sf::Keyboard::Key leftMoveKey = sf::Keyboard::Left;
    sf::Keyboard::Key rightMoveKey = sf::Keyboard::Right;
    sf::Keyboard::Key upMoveKey = sf::Keyboard::Up;
    sf::Keyboard::Key downMoveKey = sf::Keyboard::Down;
    sf::Keyboard::Key shotKey = sf::Keyboard::Space;
    
    this->player->left = leftMoveKey;
    this->player->right = rightMoveKey;
    this->player->up = upMoveKey;
    this->player->down = downMoveKey;
    this->player->shot = shotKey;
    
    this->player->setPosition(300.f, 450.f); //Ustawienie pozycji poczatkowej gracza

}
void Game::stworzObiektPrzeciwnik() //Metoda do tworzenia obiektu przeciwnika
{
    this->enemy = new Player(); //Utworzenie obiektu nowego obiektu (przeciwnik)

    sf::Keyboard::Key leftMoveKey = sf::Keyboard::A;
    sf::Keyboard::Key rightMoveKey = sf::Keyboard::D;
    sf::Keyboard::Key upMoveKey = sf::Keyboard::W;
    sf::Keyboard::Key downMoveKey = sf::Keyboard::S;
    sf::Keyboard::Key shotKey = sf::Keyboard::LControl;

    this->enemy->left = leftMoveKey;
    this->enemy->right = rightMoveKey;
    this->enemy->up = upMoveKey;
    this->enemy->down = downMoveKey;
    this->enemy->shot = shotKey;

    this->enemy->setPosition(500, 550); //Ustawienie pozycji pocz�tkowej drugiego gracza (przeciwnik)


}

void Game::stworzCegly()
{
    int x = 100, y=75;
    
    //cegly poziome gora
    for (int i = 0; i < 25; i++)
    {
        this->bricks.push_back(new Bricks(this->textures["BRICKS"], x, y, 1.f));
        x += 25;
       
    }
    

}

// Konstuktor 
Game::Game()
{
    //Inicjacja wszystkich metod (podstawowe elementy do gry)
    this->stworzZmienne();
    this->stworzOkno();
    this->stworzTekstury();
    this->stworzObiektGracz();
    this->stworzObiektPrzeciwnik();
    this->stworzCegly();
}

// Destruktor
Game::~Game()
{
    delete this->window; //Usuwa okno gry
    delete this->player; //Usuwa obiekt gracza
    delete this->enemy; // Usuwa obiekt przeciwnika
    

    //usuwanie tekstur (mapa)
    for (auto& i : this->textures) //Iteracja po wszystkich teksturach z mapy "textures"
    {
        delete i.second; //Usuwa wszystkie textury
    }

    for (auto* i : this->bullets)
    {
        delete i; // usuwa wszystkie obiekty pocisk�w z wektora "bullets"
    }

    for (auto* i : this->bricks)
    {
        delete i; // usuwa wszystkie obiekty pocisk�w z wektora "bullets"
    }
}


void Game::run() //G��wna petla gry
{
    //W ka�dej iteracji petli podczas uruchomionego okna wywo�uje metody update() i render()
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }

}

//Funkcje
void Game::spawnEnemy()
{


}

void Game::destroy()
{
    delete this; // Usuwa obiekt gry
}



void Game::pollEvents()
{
    //Podczas otwartego okna
    while (this->window->pollEvent(this->ev))
    {
        //Zmiana dzialania
        switch (this->ev.type)
        {
            //zamykanie gry przyciskiem
        case sf::Event::Closed:
            this->window->close();
            break;
            //zamykanie gry klawiszem escape
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

void Game::updatePlayer(Player* player)
{
    //Poruszanie obiektu gracza
    if (sf::Keyboard::isKeyPressed(player->left)) //Lewa strza�ka
    {
        player->move(-1.f, 0.f); //Kierunek poruszania
        player->rotate_ob(270); //Obr�t obiektu

    }
    else if (sf::Keyboard::isKeyPressed(player->right))//analogicznie jak wy�ej tylko w prawo
    {
        player->move(1.f, 0.f);
        player->rotate_ob(90);

    }
    else if (sf::Keyboard::isKeyPressed(player->up))//analogicznie jak wy�ej tylko do g�ry
    {
        player->move(0.f, -1.f);
        player->rotate_ob(0);

    }

    else if (sf::Keyboard::isKeyPressed(player->down))//analogicznie jak wy�ej tylko w d�
    {
        player->move(0.f, 1.f);
        player->rotate_ob(180);

    }
    //Poruszanie obiektu gracza koniec

    if (sf::Keyboard::isKeyPressed(this->player->shot))
    {

        time = clock.getElapsedTime();
        //opoznienie miedzy strzalami
        if (time.asSeconds() > 0.5)
        {
            int angle = (int)this->player->ob_rotation();
            switch (angle)//ustawianie kierunku strza�u
            {
            case(0):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y - 25, 0.f, -1.f, 2.f));
                clock.restart(); //Resetowanie zegara po wystrzeleniu pocisku
                break;
            }
            case(90):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 25, this->player->getPos().y, 1.f, 0.f, 2.f));
                clock.restart();
                break;
            }
            case(180):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y + 25, 0.f, 1.f, 2.f));
                clock.restart();
                break;
            }
            case(270):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x - 25, this->player->getPos().y, -1.f, 0.f, 2.f));
                clock.restart();
                break;
            }

            }
        }
    }

    if (sf::Keyboard::isKeyPressed(this->enemy->shot))
    {


        time = clock.getElapsedTime();
        //opoznienie miedzy strzalami
        if (time.asSeconds() > 0.5)
        {
            int angle = (int)this->enemy->ob_rotation();
            switch (angle)//ustawianie kierunku strza�u
            {
            case(0):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x, this->enemy->getPos().y - 25, 0.f, -1.f, 2.f));
                clock.restart(); //Resetowanie zegara po wystrzeleniu pocisku
                break;
            }
            case(90):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x + 25, this->enemy->getPos().y, 1.f, 0.f, 2.f));
                clock.restart();
                break;
            }
            case(180):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x, this->enemy->getPos().y + 25, 0.f, 1.f, 2.f));
                clock.restart();
                break;
            }
            case(270):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x - 25, this->enemy->getPos().y, -1.f, 0.f, 2.f));
                clock.restart();
                break;
            }

            }
        }
    }

}

void Game::updateBricks()
{
    for (auto* brick : bricks) // Dla ka�dej ceg�y w wektorze bricks
    {
        if (player->getBounds().intersects(brick->getBounds())) // Sprawd�, czy gracz koliduje z ceg��
        {
             // Zniszcz ceg��
        }

        for (auto* bullet : bullets) // Dla ka�dego pocisku w wektorze bullets
        {
            if (bullet->getBounds().intersects(brick->getBounds())) // Sprawd�, czy pocisk koliduje z ceg��
            {
                // Zniszcz pocisk
                // Zniszcz ceg��
            }
        }
    }

    // Usu� zniszczone ceg�y z wektora bricks
    
}



            //Top collision
            if (playerbounds.top > wallbounds.top &&
                playerbounds.top + playerbounds.height > wallbounds.top + 25
                && playerbounds.left<wallbounds.left + 25
                && playerbounds.left + 25 >wallbounds.left)
            {
                cout << "kolizja dolna\n";
                player->setPosition(playerbounds.left + 25, wallbounds.top + wallbounds.height + 25);
            }


            //Right collision
            if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top<wallbounds.top + 25
                && playerbounds.top + 25 >wallbounds.top)
            {
                cout << "lewa kolizja\n";
                object->setPosition(wallbounds.left - playerbounds.width + 25, playerbounds.top + 25);
                //Left collision
            }
            if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top<wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >wallbounds.top)
            {
                cout << "prawa kolizja\n";
                object->setPosition(wallbounds.left + wallbounds.width + 25, playerbounds.top + 25);
            }


        }
    }

}

void Game::Playerscollisions(Player *object,Player *object2)

{
    sf::FloatRect nextpos;
    

        sf::FloatRect playerbounds = object->getBounds();
        sf::FloatRect player1bounds = object2->getBounds();

        sf::FloatRect wallbounds = object2->getBounds();
        nextpos = playerbounds;

        //  nextpos = player->getBounds().left;

        if (wallbounds.intersects(nextpos))
        {

            //Bottom collision
            if (playerbounds.top < wallbounds.top &&
                playerbounds.top + playerbounds.height < wallbounds.top + 25
                && playerbounds.left<wallbounds.left + 25
                && playerbounds.left + playerbounds.width >wallbounds.left)
            {
                cout << "kolizja od gory\n";
                object->setPosition(playerbounds.left + playerbounds.width - 25, wallbounds.top - playerbounds.height + 25);
                


                
            }

            //Top collision
            if (playerbounds.top > wallbounds.top &&
                playerbounds.top + playerbounds.height > wallbounds.top + 25
                && playerbounds.left<wallbounds.left + 25
                && playerbounds.left + 25 >wallbounds.left)
            {
                cout << "kolizja dolna\n";
              object->setPosition(playerbounds.left + 25, wallbounds.top + wallbounds.height + 25);
                
            }


            //Right collision
            if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top<wallbounds.top + 25
                && playerbounds.top + 25 >wallbounds.top)
            {
                cout << "lewa kolizja\n";
                object->setPosition(wallbounds.left - playerbounds.width + 25, playerbounds.top + 25);
                
                //Left collision
            }
            if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top<wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >wallbounds.top)
            {
                cout << "prawa kolizja\n";
                object->setPosition(wallbounds.left + wallbounds.width + 25, playerbounds.top + 25);
            }


        }
    
}

void Game::bulletcollision(Player* object)
{
    sf::FloatRect nextpos;
    int licznik = 0;
    for (auto* bullet : this->bullets) // Dla kazdej cegly w wektorze bricks
    {
    sf::FloatRect nextpos;

    
    sf::FloatRect playerbounds = object->getBounds();
    sf::FloatRect wallbounds = bullet->getBounds();
    nextpos = playerbounds;

    //  nextpos = player->getBounds().left;

    if (wallbounds.intersects(nextpos))
    {

        //Bottom collision
        if (playerbounds.top < wallbounds.top &&
            playerbounds.top + playerbounds.height < wallbounds.top + 25
            && playerbounds.left<wallbounds.left + 25
            && playerbounds.left + playerbounds.width >wallbounds.left)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowan� pami�� pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            cout << "punkt";
            object->hp--;
            cout << object->hp;
            licznik--;
           // delete bullet;

        }

        //Top collision
        if (playerbounds.top > wallbounds.top &&
            playerbounds.top + playerbounds.height > wallbounds.top + 25
            && playerbounds.left<wallbounds.left + 25
            && playerbounds.left + 25 >wallbounds.left)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowan� pami�� pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            cout << "punkt";
            object->hp--;
            cout << object->hp;
            licznik--;
          //  delete bullet;
        }


        //Right collision
        if (playerbounds.left < wallbounds.left &&
            playerbounds.left + 25 < wallbounds.left + 25
            && playerbounds.top<wallbounds.top + 25
            && playerbounds.top + 25 >wallbounds.top)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowan� pami�� pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            cout << "punkt";
            object->hp--;
            cout << object->hp;
            licznik--;
          //  delete bullet;

            //Left collision
        }
        if (playerbounds.left > wallbounds.left &&
            playerbounds.left + 25 > wallbounds.left + wallbounds.width
            && playerbounds.top<wallbounds.top + wallbounds.height
            && playerbounds.top + 25 >wallbounds.top)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowan� pami�� pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            cout << "punkt";
            object->hp--;
            cout << object->hp;
            licznik--;
            //delete bullet;
            
        }
        
    }
    licznik++;
    }

}
void Game::updateBullets() //Metoda do usuwania pociskow
{
    unsigned int licznik = 0;

    for (auto* bullet : this->bullets) //W kazdej iteracji wska�nik bullet wskazuje na kolejny element wektora "bullets"
    {
        bullet->update(); //wywolanie metody update() dla kazdego pocisku

        //pozycja pocisku do okna gry

        //g�ra ekranu
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowan� pami�� pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            licznik--; //dekrementacja licznika po usunieciu pocisku

            cout << "Pocisk gora: " << this->bullets.size() << endl; //Wyswietlenie na standardowym wyj�ciu informacji o liczbie obecnych pociskow
        }

        //lewa strona ekranu
        else if (bullet->getBounds().left + bullet->getBounds().width < 0.f) //Sprawdza czy lewa kraw�d� pocisku jest poza granica okna gry
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--; 

            cout << "Pocisk lewa: " << this->bullets.size() << endl; //Wyswietlenie na standardowym wyj�ciu informacji o liczbie obecnych pociskow
        }

        //prawa strona ekranu
        else if (bullet->getBounds().left > this->window->getSize().x) //Analogicznie jak wy�ej tylko warunek dla prawej strony ekranu
        {
            delete this->bullets.at(licznik); //dealokacja pamieci
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku z wektora
            licznik--;

            cout << "Pocisk prawa: " << this->bullets.size() << endl;
        }

        //dol ekranu
        else if (bullet->getBounds().top > this->window->getSize().y) //Analogicznie jak wy�ej tylko warunek dla dolnej granicy ekranu
        {
            delete this->bullets.at(licznik);//dealokacja pamieci
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku z wektora
            licznik--;

            cout << "Pocisk dol: " << this->bullets.size() << endl;
        }

        licznik++; //inkrementacja aby przejsc do kolejnego elementu wektora "bullets"
    }

}


void Game::update()
{
    this->pollEvents();

    this->updatePlayer(player);
    this->updatePlayer(enemy);
    this->Playerscollisions(enemy, player);
    this->Playerscollisions(player, enemy);
   

    this->updateBricks();
    this->updateBullets();
    this->player->update();
    this->enemy->update();
    

    this->updateEnemies();

}

void Game::renderEnemies()
{
    this->enemy->render(*this->window); //Wyswietlenie obiektu przeciwnika
    enemy->color_change(); //Zmiana koloru obiektu przeciwnika
}

void Game::render()
{
    this->window->clear(); //czysci okno gry


    this->renderEnemies();
    this->player->render(*this->window); //Rysuje obiekt gracza na ekranie

    for (auto* bricks : this->bricks) //Dla ka�dego obiektu w wektorze
    {
        //bez this?
        bricks->render(*this->window); //Wyswietla ka�dy obiekt na ekranie
    }

    for (auto* bullet : this->bullets) //Dla ka�dego obiektu w wektorze
    {
        bullet->render(this->window); //Wyswietla ka�dy obiekt na ekranie
    }

    


    this->window->display(); //Wyswietla na ekranie obecnie narysowane obiekty

}
