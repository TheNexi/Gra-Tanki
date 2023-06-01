#include "Game.h"
#include <iostream>

using namespace std;

//Metody prywatne
void Game::stworzZmienne()
{
    this->window = nullptr; //Inicjalizacja pola window na pusty wskaźnik
    this->endGame = false;

}

void Game::stworzOkno() //Metoda do tworzenia okna gry
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gra Tanki", sf::Style::Close); //Utworzenie nowego obiektu klasy RenderWindow


    this->window->setFramerateLimit(144); //Limit klatek na sekunde
    this->window->setVerticalSyncEnabled(false); //wyłączenie synchorizacji pionowej

}
void Game::stworzTekstury() //Metoda do załadowania tekstur z pliku
{
    this->textures["BULLET"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BULLET"]->loadFromFile("Textures/bullet2.png"); //Ładowanie tekstury pocisku z pliku

    this->textures["BRICKS"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BRICKS"]->loadFromFile("Textures/brick50.png"); //Ładowanie tekstury pocisku z pliku


}
void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
    {
        cout << "Blad w Game::initFonts()";
    }

}
void Game::initGuiText()
{
    this->guiTextPlayer.setFont(this->font);
    this->guiTextPlayer.setFillColor(sf::Color::Blue);
    this->guiTextPlayer.setCharacterSize(24);
    this->guiTextPlayer.setPosition(0.f, 550.f);

    this->guiTextEnemy.setFont(this->font);
    this->guiTextEnemy.setFillColor(sf::Color::Green);
    this->guiTextEnemy.setCharacterSize(24);
    this->guiTextEnemy.setPosition(0.f, 0.f);
}
void Game::updateGui()
{
    stringstream ssplayer;
    stringstream ssenemy;
    ssplayer << "Points: " << player->points;

    ssplayer << "\nHp: " << enemy->hp;

    ssenemy << "Points: " << enemy->points;
    ssenemy << "\nHp: " << player->hp;

    this->guiTextPlayer.setString(ssplayer.str());
    this->guiTextEnemy.setString(ssenemy.str());


    //Tekst zakonczenia gry
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(250.f, 300.f);

    //this->endGameText.setString("Blue team won!");

    if (enemy->hp == 0)
    {
        this->endGameText.setString("Green team won!");
    }
    else if (player->hp == 0)
    {
        this->endGameText.setString("Blue team won!");
    }
    else if (orzel->destructionHp == 0)
    {
        this->endGameText.setString("Blue team won!");
    }

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
    this->player->hp = 10;
    this->player->points = 0;

    this->player->setPosition(700.f, 450.f); //Ustawienie pozycji poczatkowej gracza

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
    this->enemy->hp = 10;
    this->enemy->points = 0;

    this->enemy->setPosition(175.f, 25.f); //Ustawienie pozycji początkowej drugiego gracza (przeciwnik)
}

void Game::stworzCegly()
{

    float xCols[] = { 100.f, 250.f, 400.f ,550.f }; // Współrzędne x dla kolumn cegieł
    float yStart = 60.f; // Początkowa współrzędna y

    for (int column = 0; column < 4; column++)
    {
        float y = yStart;

        for (int row = 0; row < 2; row++)
        {
            this->bricks.push_back(new Bricks(this->textures["BRICKS"], xCols[column], y, 1.f));

            y += 50.f;
        }

    }

    //Cegły linia pozioma
    float xStart = 1.f;
    yStart = 160.f;

    for (int column = 0; column < 1; column++)
    {

        float x = xStart;

        for (int row = 0; row < 16; row++)
        {
            this->bricks.push_back(new Bricks(this->textures["BRICKS"], x, yStart, 1.f));

            x += 50.f;
        }

    }

    //Cegly dla orzelka

    xStart = 350.f;
    yStart = 500.f;

    for (int column = 0; column < 1; column++)
    {
        float x = xStart;
        for (int row = 0; row < 4; row++)
        {
            this->bricks.push_back(new Bricks(this->textures["BRICKS"], x, yStart, 1.f));

            x += 50.f;
        }
    }
    xStart = 350.f;
    yStart = 550.f;

    for (int column = 0; column < 1; column++)
    {
        float x = xStart;
        for (int row = 0; row < 2; row++)
        {
            this->bricks.push_back(new Bricks(this->textures["BRICKS"], x, yStart, 1.f));

            x += 150.f;
        }

    }

    xStart = 275.f;
    yStart = 275.f;

    for (int column = 0; column < 4; column++)
    {
        float x = xStart;
        float y = yStart;

        for (int row = 0; row < 3; row++)
        {
            this->bricks.push_back(new Bricks(this->textures["BRICKS"], x, yStart, 1.f));

            x += 125.f;
            y += 75.f;
        }

    }


}

void Game::stworzFlage()
{
    this->orzel = new Flag();

    orzel->setPosition(450.f, 550.f);

}


// Konstuktor 
Game::Game()
{
    //Inicjacja wszystkich metod (podstawowe elementy do gry)
    this->stworzZmienne();
    this->stworzOkno();
    this->stworzTekstury();
    this->initFonts();
    this->initGuiText();
    this->stworzObiektGracz();
    this->stworzObiektPrzeciwnik();
    this->spawnEnemy();
    this->stworzCegly();
    this->stworzFlage();
}

// Destruktor
Game::~Game()
{
    delete this->window; //Usuwa okno gry
    delete this->player; //Usuwa obiekt gracza
    delete this->enemy; // Usuwa obiekt przeciwnika
    delete this->orzel; //Usuwa obiekt flagi

    //usuwanie tekstur (mapa)
    for (auto& i : this->textures) //Iteracja po wszystkich teksturach z mapy "textures"
    {
        delete i.second; //Usuwa wszystkie textury
    }

    for (auto* i : this->bullets)
    {
        delete i; // usuwa wszystkie obiekty pocisków z wektora "bullets"
    }

    for (auto* i : this->bricks)
    {
        delete i; // usuwa wszystkie obiekty pocisków z wektora "bullets"
    }
}


void Game::run() //Główna petla gry
{
    //W każdej iteracji petli podczas uruchomionego okna wywołuje metody update() i render()
    while (this->window->isOpen() && this->endGame == false)
    {

        this->update();
        this->render();

        if (this->endGame == true)
        {
            sf::sleep(sf::seconds(3.f));
        }

    }

}

//Funkcje
void Game::spawnEnemy()
{
    this->bot = new Player();

    this->bot = new Player(); //Utworzenie obiektu nowego obiektu (przeciwnik)

    this->bot->color_change();
    this->bot->hp = 10;
    this->bot->points = 0;

    this->bot->setPosition(260.f, 25.f); //Ustawienie pozycji 

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

//void Game::updateEnemies(Player* object)
//{
//   
//}
void Game::logic_enemy(Player* object)
{
    
        m_down(object);
        this->Brickscollisions(object);
    
}

void Game::m_left(Player* object)
{
    object->move(-1.f, 0.f); //Kierunek poruszania
    object->rotate_ob(270); //Obrót obiektu
}
void Game::m_right(Player* object)
{
    object->move(1.f, 0.f);
    object->rotate_ob(90);
}
void Game::m_up(Player* object)
{
    object->move(0.f, -1.f);
    object->rotate_ob(0);
}
void Game::m_down(Player* object)
{
    object->move(0.f, 1.f);
    object->rotate_ob(180);
}


void Game::updatePlayer(Player* player)
{
    //Poruszanie obiektu gracza
    if (sf::Keyboard::isKeyPressed(player->left)) //Lewa strzałka
    {
        player->move(-1.f, 0.f); //Kierunek poruszania
        player->rotate_ob(270); //Obrót obiektu

    }
    else if (sf::Keyboard::isKeyPressed(player->right))//analogicznie jak wyżej tylko w prawo
    {
        player->move(1.f, 0.f);
        player->rotate_ob(90);

    }
    else if (sf::Keyboard::isKeyPressed(player->up))//analogicznie jak wyżej tylko do góry
    {
        player->move(0.f, -1.f);
        player->rotate_ob(0);
    }

    else if (sf::Keyboard::isKeyPressed(player->down))//analogicznie jak wyżej tylko w dół
    {
        player->move(0.f, 1.f);
        player->rotate_ob(180);
    }
    //Poruszanie obiektu gracza koniec

    if (sf::Keyboard::isKeyPressed(this->player->shot))
    {
        /*
        sf::SoundBuffer buff;

        if (!buff.loadFromFile("boom2.wav"))
        {
            cout << "\n-----------------blad-----------\n";

        }

        sf::Sound sound;
        sound.setBuffer(buff);
        cout << "\n\n dzwiek\n\n";

        if (sound.getStatus() != sf::Sound::Playing)
        {
            sound.play();
            cout << "gra muzyka\n";
        }
        */
        /*
        sf::Music music;
        music.openFromFile("boom2.wav");
        music.setVolume(50);
        music.play();
        */

        time = clock.getElapsedTime();
        //opoznienie miedzy strzalami
        if (time.asSeconds() > 0.5)
        {
            int angle = (int)this->player->ob_rotation();
            switch (angle)//ustawianie kierunku strzału
            {
            case(0):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y - 35, 0.f, -1.f, 2.f, "player"));
                clock.restart(); //Resetowanie zegara po wystrzeleniu pocisku

                break;
            }
            case(90):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 25, this->player->getPos().y, 1.f, 0.f, 2.f, "player"));
                clock.restart();
                break;
            }
            case(180):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x, this->player->getPos().y + 25, 0.f, 1.f, 2.f, "player"));
                clock.restart();
                break;
            }
            case(270):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x - 35, this->player->getPos().y, -1.f, 0.f, 2.f, "player"));
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
            switch (angle)//ustawianie kierunku strzału
            {
            case(0):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x, this->enemy->getPos().y - 36, 0.f, -1.f, 2.f, "enemy"));
                clock.restart(); //Resetowanie zegara po wystrzeleniu pocisku
                break;
            }
            case(90):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x + 25, this->enemy->getPos().y, 1.f, 0.f, 2.f, "enemy"));
                clock.restart();
                break;
            }
            case(180):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x, this->enemy->getPos().y + 26, 0.f, 1.f, 2.f, "enemy"));
                clock.restart();
                break;
            }
            case(270):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], this->enemy->getPos().x - 35, this->enemy->getPos().y, -1.f, 0.f, 2.f, "enemy"));
                clock.restart();
                break;
            }

            }
        }

    }

    if (player->hp <= 0)
    {
        this->endGame = true;
    }

}

void Game::updateBricks(Player* object)
{
    Brickscollisions(object);



    int bulletIndexToRemove = -1; // Indeks pocisku do usunięcia (-1 oznacza brak usuwania)
    int brickIndexToRemove = -1; // Indeks cegły do usunięcia (-1 oznacza brak usuwania)
    int bulletIndex; //Zmienna do przechowywania biezacego indeksu pocisku
    int brickIndex;  //Zmienna do przechowywania biezacego indeksu cegły


    for (bulletIndex = 0; bulletIndex < this->bullets.size(); bulletIndex++)
    {
        for (brickIndex = 0; brickIndex < this->bricks.size(); brickIndex++)
        {
            if (this->bullets[bulletIndex]->getBounds().intersects(this->bricks[brickIndex]->getBounds())) //Sprawdzenie czy granice obiektu pocisku nakładają się na granice obiektu cegły
            {
                // Kolizja pocisku z cegłą
                bulletIndexToRemove = bulletIndex; //Ustawienie indeksu pocisku ktory sie zetknal z cegłą
                brickIndexToRemove = brickIndex;   //Ustawienie indeksu cegly z ktora sie zetknal pocisk
                break; //Przerwanie petli po zetknieciu jednego pocisku z jedną cegłą
            }
        }

        if (bulletIndexToRemove != -1 && brickIndexToRemove != -1) //Sprawdzenie czy wystąpiła kolizja
        {

            // Usuwanie pocisku
            //object->points += 1;
            delete this->bullets[bulletIndexToRemove];
            this->bullets.erase(this->bullets.begin() + bulletIndexToRemove);

            // Usuwanie cegły
            delete this->bricks[brickIndexToRemove];
            this->bricks.erase(this->bricks.begin() + brickIndexToRemove);

            // Zmniejszenie indeksów dla pętli, aby uwzględnić usuwanie elementów
            if (bulletIndexToRemove < bulletIndex)
            {
                bulletIndex--;
            }
            if (brickIndexToRemove < brickIndex)
            {
                brickIndex--;
            }

            // Zresetowanie indeksów do braku usuwania
            bulletIndexToRemove = -1;
            brickIndexToRemove = -1;
        }
    }


}


void Game::Brickscollisions(Player* object)
{


    sf::FloatRect nextpos;
    for (auto& brick : bricks) // Dla kazdej cegly w wektorze bricks
    {

        sf::FloatRect playerbounds = object->getBounds();

        sf::FloatRect wallbounds = brick->getBounds();
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

}

void Game::Playerscollisions(Player* object, Player* object2)

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

void Game::Playerscollisions(Player* object, Flag* object2)

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

void Game::boom_sound()
{

}
void Game::bulletcollision(Player* object)
{
    sf::FloatRect nextpos;
    int licznik = 0;



    for (auto* bullet : this->bullets) // Dla kazdej cegly w wektorze bullets
    {
        sf::FloatRect nextpos;

        sf::FloatRect playerbounds = object->getBounds();
        sf::FloatRect wallbounds = bullet->getBounds();
        nextpos = playerbounds;

        //  nextpos = player->getBounds().left;

        if (wallbounds.intersects(nextpos)) {




            //Bottom collision
            if (playerbounds.top < wallbounds.top &&
                playerbounds.top + playerbounds.height < wallbounds.top + 25
                && playerbounds.left<wallbounds.left + 25
                && playerbounds.left + playerbounds.width >wallbounds.left)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->points += 10;

                cout << "\nhp: ";
                object->hp--;
                cout << object->hp << endl;
                licznik--;
                // delete bullet;

            }

            //Top collision
            else if (playerbounds.top > wallbounds.top &&
                playerbounds.top + playerbounds.height > wallbounds.top + 25
                && playerbounds.left<wallbounds.left + 25
                && playerbounds.left + 25 >wallbounds.left)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->points += 10;
                cout << "\nhp: ";
                object->hp--;
                cout << object->hp << endl;
                licznik--;
                //  delete bullet;
            }


            //Right collision
            else if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top<wallbounds.top + 25
                && playerbounds.top + 25 >wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->points += 10;
                cout << "\nhp: ";
                object->hp--;
                cout << object->hp << endl;
                licznik--;
                // delete bullet;

            }
            //Left collision
            else if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top<wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->points += 10;
                cout << "\nhp: ";
                object->hp--;
                cout << object->hp << endl;
                licznik--;
                //delete bullet;

            }

        }
        licznik++;
    }

}

void Game::bulletcollision(Flag* object)
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
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->destructionHp--;

                cout << "Orzelek hp: ";

                cout << object->destructionHp;
                licznik--;
                // delete bullet;

            }

            //Top collision
            else if (playerbounds.top > wallbounds.top &&
                playerbounds.top + playerbounds.height > wallbounds.top + 25
                && playerbounds.left<wallbounds.left + 25
                && playerbounds.left + 25 >wallbounds.left)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->destructionHp--;

                cout << "Orzelek hp: ";

                cout << object->destructionHp;
                licznik--;
                //  delete bullet;
            }


            //Right collision
            else if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top<wallbounds.top + 25
                && playerbounds.top + 25 >wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->destructionHp--;

                cout << "Orzelek hp: ";

                cout << object->destructionHp;
                licznik--;
                // delete bullet;

            }
            //Left collision
            else if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top<wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->destructionHp--;

                cout << "Orzelek hp: ";

                cout << object->destructionHp;
                licznik--;
                //delete bullet;

            }

        }
        licznik++;
    }
    if (object->destructionHp <= 0)
    {
        this->endGame = true;

    }

}

void Game::updateBullets() //Metoda do usuwania pociskow
{
    unsigned int licznik = 0;


    for (auto* bullet : this->bullets) //W kazdej iteracji wskaźnik bullet wskazuje na kolejny element wektora "bullets"
    {
        bullet->update(); //wywolanie metody update() dla kazdego pocisku

        //pozycja pocisku do okna gry

        //góra ekranu
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            licznik--; //dekrementacja licznika po usunieciu pocisku

            cout << "Pocisk gora: " << this->bullets.size() << endl; //Wyswietlenie na standardowym wyjściu informacji o liczbie obecnych pociskow
        }

        //lewa strona ekranu
        else if (bullet->getBounds().left + bullet->getBounds().width < 0.f) //Sprawdza czy lewa krawędź pocisku jest poza granica okna gry
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--;

            cout << "Pocisk lewa: " << this->bullets.size() << endl; //Wyswietlenie na standardowym wyjściu informacji o liczbie obecnych pociskow
        }

        //prawa strona ekranu
        else if (bullet->getBounds().left > this->window->getSize().x) //Analogicznie jak wyżej tylko warunek dla prawej strony ekranu
        {
            delete this->bullets.at(licznik); //dealokacja pamieci
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku z wektora
            licznik--;

            cout << "Pocisk prawa: " << this->bullets.size() << endl;
        }

        //dol ekranu
        else if (bullet->getBounds().top > this->window->getSize().y) //Analogicznie jak wyżej tylko warunek dla dolnej granicy ekranu
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

    //this->updateGui(enemy);
    this->Playerscollisions(player, enemy);
    this->Playerscollisions(bot, enemy);
    this->Playerscollisions(enemy, bot);
    this->Playerscollisions(player, orzel);
    this->Playerscollisions(enemy, orzel);
   

    this->updateBricks(player);
    this->updateBricks(enemy);
    this->logic_enemy(bot);

    //this->Playerscollisions(player, enemy);
    this->bulletcollision(player);
    this->bulletcollision(enemy);
    this->bulletcollision(orzel);

    this->updateBricks(player);
    this->updateBricks(enemy);
    this->updateBullets();
    this->player->update();
    this->enemy->update();


    

    this->updateGui();
}

void Game::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiTextPlayer);
    target->draw(this->guiTextEnemy);

}

void Game::renderEnemies()
{
    this->enemy->render(*this->window); //Wyswietlenie obiektu przeciwnika
    enemy->color_change(); //Zmiana koloru obiektu przeciwnika
}

void Game::render()
{
    this->window->clear(); //czysci okno gry

    this->renderGui(this->window);
    this->renderEnemies();
    this->player->render(*this->window); //Rysuje obiekt gracza na ekranie
    this->orzel->render(*this->window);
    this->bot->render(*this->window);

    for (auto* bricks : this->bricks) //Dla każdego obiektu w wektorze
    {
        bricks->render(*this->window); //Wyswietla każdy obiekt na ekranie
    }

    for (auto* bullet : this->bullets) //Dla każdego obiektu w wektorze
    {
        bullet->render(this->window); //Wyswietla każdy obiekt na ekranie
    }

    //Wyswietlenie informacji o zakonczeniu rozgrywki
    if (this->endGame == true)
    {
        this->window->draw(this->endGameText);
    }


    this->window->display(); //Wyswietla na ekranie obecnie narysowane obiekty

}
