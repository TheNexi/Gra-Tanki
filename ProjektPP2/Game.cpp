#include "Game.h"

using namespace std;

//Metody prywatne
void Game::stworzZmienne()
{
    this->window = nullptr; //Inicjalizacja pola window na pusty wskaŸnik
}

void Game::stworzOkno() //Metoda do tworzenia okna gry
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gra Tanki", sf::Style::Close); //Utworzenie nowego obiektu klasy RenderWindow
    

    this->window->setFramerateLimit(144); //Limit klatek na sekunde
    this->window->setVerticalSyncEnabled(false); //wy³¹czenie synchorizacji pionowej

}
void Game::stworzTekstury() //Metoda do za³adowania tekstur z pliku
{
    this->textures["BULLET"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BULLET"]->loadFromFile("Textures/bullet2.png"); //£adowanie tekstury pocisku z pliku

}
void Game::stworzObiektGracz() //Metoda do tworzenia obiektu gracza
{
    this->player = new Player(); //Utworzenie obiektu gracza

    
    this->player->setPosition(300.f, 450.f); //Ustawienie pozycji poczatkowej gracza

}
void Game::stworzObiektPrzeciwnik() //Metoda do tworzenia obiektu przeciwnika
{
    this->enemy = new Player(); //Utworzenie obiektu nowego obiektu (przeciwnik)

    this->enemy->setPosition(500, 550); //Ustawienie pozycji pocz¹tkowej drugiego gracza (przeciwnik)


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
}

// Destruktor
Game::~Game()
{
    delete this->window; //Usuwa okno gry
    delete this->player; //Usuwa obiekt gracza

    //usuwanie tekstur (mapa)
    for (auto& i : this->textures) //Iteracja po wszystkich teksturach z mapy "textures"
    {
        delete i.second; //Usuwa wszystkie textury
    }

    for (auto* i : this->bullets)
    {
        delete i; // usuwa wszystkie obiekty pocisków z wektora "bullets"
    }
}


void Game::run() //G³ówna petla gry
{
    //W ka¿dej iteracji petli podczas uruchomionego okna wywo³uje metody update() i render()
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

void Game::updatePlayer()
{
    //Poruszanie obiektu gracza
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) //Lewa strza³ka
    {
        this->player->move(-1.f, 0.f); //Kierunek poruszania
        this->player->rotate_ob(270); //Obrót obiektu

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//analogicznie jak wy¿ej tylko w prawo
    {
        this->player->move(1.f, 0.f);
        this->player->rotate_ob(90);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//analogicznie jak wy¿ej tylko do góry
    {
        this->player->move(0.f, -1.f);
        this->player->rotate_ob(0);

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//analogicznie jak wy¿ej tylko w dó³
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
            switch (angle)//ustawianie kierunku strza³u
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

}




void Game::updateBullets()//zmiana 
{
    unsigned int licznik = 0;

    for (auto* bullet : this->bullets) //W kazdej iteracji wskaŸnik bullet wskazuje na kolejny element wektora "bullets"
    {
        bullet->update(); //wywolanie metody update() dla kazdego pocisku

        //pozycja pocisku do okna gry

        //góra ekranu
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
        {
            delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowan¹ pamiêæ pocisku o indeksie licznik w wektorze bullets
            this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
            licznik--; //dekrementacja licznika po usunieciu pocisku

            cout << "Pocisk gora: " << this->bullets.size() << endl; //Wyswietlenie na standardowym wyjœciu informacji o liczbie obecnych pociskow
        }

        //lewa strona ekranu
        else if (bullet->getBounds().left + bullet->getBounds().width < 0.f) //Sprawdza czy lewa krawêdŸ pocisku jest poza granica okna gry
        {
            delete this->bullets.at(licznik);
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku
            licznik--; 

            cout << "Pocisk lewa: " << this->bullets.size() << endl; //Wyswietlenie na standardowym wyjœciu informacji o liczbie obecnych pociskow
        }

        //prawa strona ekranu
        else if (bullet->getBounds().left > this->window->getSize().x) //Analogicznie jak wy¿ej tylko warunek dla prawej strony ekranu
        {
            delete this->bullets.at(licznik); //dealokacja pamieci
            this->bullets.erase(this->bullets.begin() + licznik);// usuwanie pocisku z wektora
            licznik--;

            cout << "Pocisk prawa: " << this->bullets.size() << endl;
        }

        //dol ekranu
        else if (bullet->getBounds().top > this->window->getSize().y) //Analogicznie jak wy¿ej tylko warunek dla dolnej granicy ekranu
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

    this->updatePlayer();


    this->updateBullets();
    this->player->update();

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

    for (auto* bullet : this->bullets) //Dla ka¿dego obiektu w wektorze
    {
        bullet->render(this->window); //Wyswietla ka¿dy obiekt na ekranie
    }

    this->window->display(); //Wyswietla na ekranie obecnie narysowane obiekty

}
