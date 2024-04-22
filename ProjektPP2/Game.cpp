#include "Game.h"
#include <iostream>

/**
 * @file Game.cpp
 * @brief Plik zrodlowy klasy Game
 */

using namespace std;

//Metody prywatne

/**
 * @brief Inicjalizuje zmienne w klasie Game.
 *
 * Funkcja inicjalizuje zmienne składowe klasy Game, takie jak window, endGame i menuRendered.
 * Pole window zostaje zainicjalizowane jako pusty wskaźnik.
 * Pole endGame jest ustawione na wartość false, oznaczającą kontynuację gry.
 * Pole menuRendered jest ustawione na wartość false, oznaczającą, że menu gry nie zostało jeszcze wyrenderowane.
 */
void Game::stworzZmienne()
{
    this->window = nullptr; //Inicjalizacja pola window na pusty wskaźnik
    this->endGame = false;
    this->menuRendered = false;
}


/**
 * @brief Tworzy okno gry.
 *
 * Metoda tworzy okno gry, tworząc nowy obiekt klasy sf::RenderWindow o określonym rozmiarze i tytule.
 * Ustawia limit liczby klatek na sekundę na 144.
 * Wyłącza synchronizację pionową.
 */
void Game::stworzOkno() //Metoda do tworzenia okna gry
{
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Gra Tanki", sf::Style::Close); //Utworzenie nowego obiektu klasy RenderWindow


    this->window->setFramerateLimit(144); //Limit klatek na sekunde
    this->window->setVerticalSyncEnabled(false); //wyłączenie synchorizacji pionowej
    
}

/**
 * @brief Ładuje tekstury z pliku.
 *
 * Metoda wczytuje tekstury z pliku i tworzy obiekty klasy sf::Texture dla poszczególnych tekstur.
 * Tekstury są przypisywane do odpowiednich kluczy w kontenerze textures.
 */
void Game::stworzTekstury() //Metoda do załadowania tekstur z pliku
{
    this->textures["BULLET"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BULLET"]->loadFromFile("Textures/bullet2.png"); //Ładowanie tekstury pocisku z pliku

    this->textures["BRICKS"] = new sf::Texture(); //Utowrzenie nowego obiektu klasy Texture
    this->textures["BRICKS"]->loadFromFile("Textures/cegla.png"); //Ładowanie tekstury pocisku z pliku

    this->textures["ENEMIES"] = new sf::Texture();
    this->textures["ENEMIES"]->loadFromFile("Textures/Tank v4.png");

}

/**
 * @brief Inicjalizuje czcionkę.
 *
 * Metoda wczytuje czcionkę z pliku "Fonts/PixellettersFull.ttf".
 * Jeśli wystąpił błąd podczas wczytywania, wyświetlany jest odpowiedni komunikat.
 */
void Game::initFonts()
{
    if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
    {
        cout << "Blad w Game::initFonts()";
    }

}
/**
 * @brief Inicjalizuje obiekty klasy sf::Text dla interfejsu graficznego.
 *
 * Metoda ustawia odpowiednie właściwości takie jak czcionka, kolor, rozmiar i pozycja dla każdego obiektu tekstu dla obiektów sf::Text, które będą wykorzystywane w interfejsie graficznym.
 */
void Game::initGuiText()
{
    this->guiTextPlayer.setFont(this->font);
    this->guiTextPlayer.setFillColor(sf::Color::Blue);
    this->guiTextPlayer.setCharacterSize(24);
    this->guiTextPlayer.setPosition(0.f, 0.f);

    this->guiTextEnemy.setFont(this->font);
    this->guiTextEnemy.setFillColor(sf::Color::Green);
    this->guiTextEnemy.setCharacterSize(24);
    this->guiTextEnemy.setPosition(700.f, 545.f);

    this->guiTextFlag.setFont(this->font);
    this->guiTextFlag.setFillColor(sf::Color::Red);
    this->guiTextFlag.setCharacterSize(24);
    this->guiTextFlag.setPosition(0.f, 550.f);

    this->guiTextBots.setFont(this->font);
    this->guiTextBots.setFillColor(sf::Color::Yellow);
    this->guiTextBots.setCharacterSize(24);
    this->guiTextBots.setPosition(0.f, 0.f);
}

/**
 * @brief Aktualizuje teksty interfejsu graficznego gracz vs gracz.
 *
 * Metoda aktualizuje teksty wyświetlane w interfejsie graficznym na podstawie bieżących danych gry.
 * Tworzy strumienie stringstream i formatuje odpowiednie informacje o punktach, pancerzu i zdrowiu.
 * Następnie ustawia te informacje jako ciągi tekstowe dla obiektów sf::Text, które są wykorzystywane w interfejsie.
 * Dodatkowo ustawia tekst informujący o zakończeniu gry, taki jak "Blue team won!" lub "Green team won!".
 */
void Game::updateGui()
{
    stringstream ssplayer;
    stringstream ssenemy;
    stringstream ssflag;
    ssplayer << "Punkty: " << player->points;
    ssplayer << "\nPancerz: " << player->hp;

    ssenemy << "Punkty: " << enemy->points;
    ssenemy << "\nPancerz: " << enemy->hp; 

    ssflag << "Flaga\nZdrowie: " << orzel->destructionHp;

    this->guiTextPlayer.setString(ssplayer.str());
    this->guiTextEnemy.setString(ssenemy.str());
    this->guiTextFlag.setString(ssflag.str());

    //Tekst zakonczenia gry
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(250.f, 300.f);

    if (enemy->hp == 0)
    {
        this->endGameText.setString("Blue team won!");
    }
    else if (player->hp == 0)
    {
        this->endGameText.setString("Green team won!");
    }
    else if (orzel->destructionHp == 0)
    {
        this->endGameText.setString("Blue team won!");
    }

}

/**
 * @brief Aktualizuje teksty interfejsu graficznego dla trybu gry z botami.
 *
 * Metoda aktualizuje teksty wyświetlane w interfejsie graficznym na podstawie bieżących danych gry w trybie z botami.
 * Tworzy strumienie stringstream i formatuje odpowiednie informacje o punktach, pancerzu, liczbie przeciwników
 * i zniszczonych przeciwnikach. Następnie ustawia te informacje jako ciągi tekstowe dla obiektów sf::Text,
 * które są wykorzystywane w interfejsie. Dodatkowo ustawia tekst informujący o zakończeniu gry, taki jak
 * "Blue team won!" lub "Yellow team won!", w zależności od tego kto zwycięży.
 */
void Game::updateGuiVsBots()
{
    stringstream ssplayer;
    stringstream ssbots;
    stringstream ssflag;

    this->guiTextPlayer.setPosition(700.f, 545.f);
    
    ssplayer << "Punkty: " << player->points;

    ssplayer << "\nPancerz: " << player->hp;

    ssbots << "Liczba przeciwnikow: " << player->numberOfEnemies;
    ssbots << "\nZniszczeni przeciwnicy: " << player->destroyedEnemies;

    ssflag << "Flaga\nZdrowie: " << orzel->destructionHp;

    this->guiTextPlayer.setString(ssplayer.str());
    this->guiTextBots.setString(ssbots.str());
    this->guiTextFlag.setString(ssflag.str());

    //Tekst zakonczenia gry
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(250.f, 300.f);

    if (player->points == 50)
    {
        this->endGameText.setString("Blue team won!");
        endGame = true;
    }
    else if (player->hp == 0)
    {
        this->endGameText.setString("Yellow team won!");
        endGame = true;
    }
    else if (orzel->destructionHp == 0)
    {
        this->endGameText.setString("Yellow team won!");
        endGame = true;
    }



}

/**
 * @brief Tworzy obiekt gracza.
 *
 * Metoda tworzy obiekt gracza i ustawia jego właściwości. Tworzony jest nowy obiekt klasy Player, a następnie
 * przypisywane są mu klawisze do poruszania się w lewo, w prawo, w górę, w dół oraz do strzału. Ustawiane są również
 * wartości początkowe dla pancerza (`hp`) i punktów (`points`) gracza. Na koniec ustawiana jest pozycja początkowa
 * gracza na ekranie.
 */
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

/**
 * @brief Tworzy obiekt przeciwnika - drugiego gracza.
 *
 * Metoda tworzy obiekt przeciwnika i ustawia jego właściwości. Tworzony jest nowy obiekt klasy Player, a następnie
 * przypisywane są mu klawisze do poruszania się w lewo, w prawo, w górę, w dół oraz do strzału. Ustawiane są również
 * wartości początkowe dla pancerza (`hp`) i punktów (`points`) gracza. Na koniec ustawiana jest pozycja początkowa
 * gracza na ekranie.
 */
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

/**
 * @brief Tworzy obiekty cegieł na planszy.
 *
 * Metoda tworzy cegły na planszy gry. Tworzone są cegły w różnych układach i pozycjach. Współrzędne x dla kolumn cegieł
 * są zdefiniowane w tablicy `xCols`, a początkowa współrzędna y to `yStart`. Następnie w pętli tworzone są cegły dla
 * kolejnych kolumn i wierszy, a ich pozycje są odpowiednio modyfikowane. Na końcu metody tworzone są specjalne cegły
 * dla elementu "orzelka", czyli flagi. Wszystkie utworzone obiekty cegieł są dodawane do wektora `bricks`.
 */
void Game::stworzCegly()
{

    float xCols[] = { 102.f, 252.f, 402.f ,552.f }; // Współrzędne x dla kolumn cegieł
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
    float xStart = 2.f;
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
    yStart = 490.f;

    for (int column = 0; column < 2; column++)
    {
        float x = xStart;
        for (int row = 0; row < 4; row++)
        {
            this->bricks.push_back(new Bricks(this->textures["BRICKS"], x, yStart, 1.f));

            x += 50.f;
        }
    }
    xStart = 350.f;
    yStart = 540.f;

    for (int column = 0; column < 2; column++)
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

    for (int column = 0; column < 1; column++)
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

/**
 * @brief Tworzy obiekt flagi na planszy.
 *
 * Metoda tworzy i inicjalizuje obiekt klasy Flag, który reprezentuje flagę na planszy gry. Flagę umieszcza na
 * konkretnej pozycji na planszy, korzystając z metody setPosition(). Utworzony obiekt flagi przypisywany jest do
 * zmiennej "orzel".
 */
void Game::stworzFlage()
{
    this->orzel = new Flag();

    orzel->setPosition(450.f, 550.f);

}


// Konstuktor 


/**
 * @brief Konstruktor klasy Game.
 *
 * Konstruktor inicjalizuje obiekt klasy Game, tworząc wszystkie niezbędne elementy do rozpoczęcia gry. Wywołuje
 * odpowiednie metody inicjalizujące pola i obiekty gry, takie jak tworzenie zmiennych, okna, tekstur, czcionek,
 * obiektu gracza, obiektów przeciwników, cegieł oraz flagi
 */
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

/**
 * @brief Destruktor klasy Game.
 *
 * Destruktor usuwa wszystkie zaalokowane zasoby i obiekty gry, takie jak okno, obiekt gracza, obiekt przeciwnika, obiekt flagi,
 * tekstury, pociski, przeciwników i cegły. Wywołuje odpowiednie operacje usuwania dla każdego zasobu lub obiektu.
 */
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
    this->bullets.clear();

    for (auto* i : this->enemies)
    {
        delete i; // usuwa wszystkie obiekty bota z wektora "enemies"
    }
    this->enemies.clear();

    for (auto* i : this->bricks)
    {
        delete i; // usuwa wszystkie obiekty cegly z wektora "bricks"
    }
    this->bricks.clear();
}

/**
 * @brief Główna pętla gry.
 *
 * Główna pętla gry, która wykonuje się dopóki okno gry jest otwarte. W każdej iteracji petli wywołuje metody update() i render(),
 * które aktualizują stan gry i renderują jej zawartość na ekranie.
 * Jeśli wystąpi żądanie powrotu do menu, resetuje grę i renderuje menu.
 * Po zakończeniu gry, oczekuje przez 3 sekundy podczas gdy wyświetlana jest informacja o wygranej jednej z drużyn, resetuje grę i przechodzi do menu.
 */
void Game::run() //Główna petla gry
{
    //W każdej iteracji petli podczas uruchomionego okna wywołuje metody update() i render()

    this->update();
    this->render();




    while (this->window->isOpen())
    {
        if (returnToMenu)
        {
            resetGame();
            renderMenu();
            returnToMenu = false;
        }
        else
        {
            this->update();
            this->render();
        }



        if (this->endGame == true)
        {
            sf::sleep(sf::seconds(3.f));
            resetGame();

            returnToMenu = true;

        }


    }

}

/**
 * @brief Renderuje menu gry.
 *
 * Renderuje menu gry na ekranie. Pętla wykonuje się dopóki menu jest aktywne.
 * Obsługuje zdarzenia dotyczące klawiszy, pozwalając na nawigację po menu i wybór opcji.
 * Po wybraniu odpowiedniej opcji, ustawia odpowiedni tryb gry (gracz vs komputer lub gracz vs gracz),
 * lub zamyka okno gry w przypadku wybrania opcji wyjścia.
 */
void Game::renderMenu()
{
    Menu menu(this->window->getSize().x, this->window->getSize().y);
    
    bool menuActive = true;  
    sf::Event event;

    while (menuActive)
    {

        while (this->window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.getPressedOption())
                    {
                    case 0:
                        cout << "Wcisnieto gracz vs komputer" << endl;
                        playervsbot = true;
                        menuActive = false;
                        break;
                    case 1:
                        cout << "Wcisnieto wyjdz" << endl;
                        this->window->close();
                        menuActive = false;
                        break;
                    
                    }

                    break;


                }

                break;
            case sf::Event::Closed:
                this->window->close();
                break;          

            }
        }

        this->window->clear();
        menu.render(*this->window);
               
    }
    this->window->display();
    
}
        

/**
 * @brief Sprawdza, czy gra powinna wrócić do menu głównego.
 *
 * @return Wartość logiczna `true`, jeśli gra powinna wrócić do menu, w przeciwnym razie `false`.
 */
bool Game::shouldReturnToMenu()
{
    return returnToMenu;
}




//Funkcje


/**
 * @brief Pobiera i obsługuje zdarzenia związane z oknem gry.
 *
 * Ta funkcja sprawdza i obsługuje różne zdarzenia związane z otwartym oknem gry, takie jak zamykanie gry przyciskiem
 * lub powrót do menu klawiszem Escape.
 */
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
                returnToMenu = true;
                //this->window->close();
            break;
            //zamykanie gry koniec
        }
    }
}
/**
 * @brief Tworzy nowych wrogów w określonym interwale czasowym.
 *
 * Ta funkcja tworzy nowych wrogów w określonym interwale czasowym, jeśli jeszcze nie została osiągnięta maksymalna liczba
 * stworzonych wrogów. Ustawia także ich pozycję początkową.
 */
void Game::spawnEnemy()
{

    float *pos_x = &bot_x;
    float *pos_y = &bot_y;
    

     spawnTime = spawnclock.getElapsedTime();

     if (spawnTime.asSeconds() > 8 && createdEnemies < 5)
     {


         Player* bot = new Player(); // Tworzenie nowego obiektu komputera

         bot->hp = 1;
         bot->bot_texture();
         // Ustawienie pozycji dla każdego obiektu gracza
         bot->setPosition(*pos_x, *pos_y);
         *pos_x += 150.f;



         enemies.push_back(bot); // Dodanie obiektu gracza do wektora enemies
         printf("\n\n\nnowy bot\n");
         
         
         spawnclock.restart();

         createdEnemies++;
     }
}
    
/**
 * @brief Aktualizuje wrogów na planszy i obsługuje ich ruchy oraz strzały.
 *
 * Ta funkcja aktualizuje wrogów na planszy, poruszając nimi i umożliwiając im strzelanie z określonym opóźnieniem. Ta funkcja również sprawdza, czy wrogowie zostali zniszczeni i wykonuje odpowiednie czynności w przypadku ich zniszczenia.
 *
 * @param object Wskaźnik na obiekt gracza, względem którego wykonywane są dane funkcje.
 *
 */
void Game::updateEnemies(Player* object)
{
   
    //Poruszanie obiektu gracza koniec

        time = clock.getElapsedTime();
        //opoznienie miedzy strzalami
        if (object->bot_destroyed == false)
        {

    
        if (time.asSeconds() > 1)
        {
            int angle = (int)object->ob_rotation();
            switch (angle)//ustawianie kierunku strzału
            {
            case(0):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], object->getPos().x, object->getPos().y - 35, 0.f, -1.f, 4.f, "player"));
                clock.restart(); //Resetowanie zegara po wystrzeleniu pocisku

                break;
            }
            case(90):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], object->getPos().x + 35, object->getPos().y, 1.f, 0.f, 4.f, "player"));
                clock.restart();
                break;
            }
            case(180):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], object->getPos().x, object->getPos().y + 35, 0.f, 1.f, 4.f, "player"));
                clock.restart();
                break;
            }
            case(270):
            {
                this->bullets.push_back(new Bullet(this->textures["BULLET"], object->getPos().x - 35, object->getPos().y, -1.f, 0.f, 4.f, "player"));
                clock.restart();
                break;
            }

            }
        }
        }
        // Sprawdzanie stanu przeciwników
     
       
           object->update();

           // Jeśli przeciwnik ma 0 punktów życia
         
           if (object->hp <= 0)
           {
               object->bot_destroyed = true;
               object->destroyed_tank_bot();  
           }   
        
}

/**
 * @brief Aktualizuje wszystkich wrogów na planszy.
 *
 * Ta funkcja iteruje przez wszystkich obiektów komputera na planszy i aktualizuje ich stan, wykonując odpowiednie działania takie jak
 * obsługa kolizji, sprawdzanie trafień pociskami oraz wywołanie logiki poruszania się komputera.
 *
 */
void Game::updateAllEnemies()
{
    for (auto& bot : enemies)
    {
        updateEnemies(bot);
        if (bot->bot_destroyed == false)
        {
            Playerscollisions(bot, player);
            Playerscollisions(player, bot);
            Playerscollisions(bot, orzel);
            
            bulletcollisionSi(player,bot);
            bulletcollisionVsSi(bot, player);

            logic_enemy(bot);
           
        }
        
    }
   
}

/**
 * @brief Logika ruchu wroga na planszy.
 *
 * Ta funkcja określa logikę ruchu wroga na planszy. Decyzje podejmowane są na podstawie pozycji wroga względem innych obiektów
 * na planszy, takich jak orzeł (oznaczający miejsce docelowe) oraz gracz. Funkcja podejmuje decyzje dotyczące kierunku ruchu
 * wroga i wykonuje odpowiednie operacje w zależności od sytuacji.
 *
 * @param object Wskaźnik na obiekt wroga.
 *
 */
void Game::logic_enemy(Player* object)
{

     if (object->getPos().y >= orzel->getBounds().top+24 && object->getPos().y <= orzel->getBounds().top+26 )
    {
         printf("prawo/lewo\n");
        if (object->getPos().x < orzel->getBounds().left)
            m_right(object);
        if (object->getPos().x > orzel->getBounds().left)
            m_left(object);
        

    }
    else
    {
         if (object->getPos().y >= player->getPos().y && object->getPos().y <= player->getPos().y)
         {
             if (object->getPos().x < player->getPos().x)
                 m_right(object);
             if (object->getPos().x > player->getPos().x)
                 m_left(object);
         }
         else
         {
             printf("down\n");
             m_down(object);
         }
    }
 
    this->Brickscollisions(object);
}

/**
 * @brief Wykonuje ruch obiektu komputera w lewo.
 *
 * Ta funkcja wykonuje ruch obiektu komputera w lewo poprzez przesunięcie obiektu na planszy o określony wektor (-0.5f, 0.f).
 * Dodatkowo, funkcja obraca obiekt o kąt 270 stopni, aby był obrócony w odpowiednim kierunku.
 *
 * @param object Wskaźnik na obiekt komputera.
 */
void Game::m_left(Player* object)
{
    object->move(-0.5f, 0.f); //Kierunek poruszania
    object->rotate_ob(270); //Obrót obiektu
}

/**
 * @brief Wykonuje ruch obiektu komputera w prawo.
 *
 * Ta funkcja wykonuje ruch obiektu komputera w prawo poprzez przesunięcie obiektu na planszy o określony wektor (0.5f, 0.f).
 * Dodatkowo, funkcja obraca obiekt o kąt 90 stopni, aby był obrócony w odpowiednim kierunku.
 *
 * @param object Wskaźnik na obiekt komputera.
 */
void Game::m_right(Player* object)
{
    object->move(0.5f, 0.f);
    object->rotate_ob(90);
}

/**
 * @brief Wykonuje ruch obiektu komputera w górę.
 *
 * Ta funkcja wykonuje ruch obiektu komputera w górę poprzez przesunięcie obiektu na planszy o określony wektor (0.f, -0.5f).
 * Dodatkowo, funkcja obraca obiekt do pozycji kąta 0 stopni, aby był obrócony w górę.
 *
 * @param object Wskaźnik na obiekt komputera.
 */
void Game::m_up(Player* object)
{
    object->move(0.f, -0.5f);
    object->rotate_ob(0);
}

/**
 * @brief Wykonuje ruch obiektu komputera w dół.
 *
 * Ta funkcja wykonuje ruch obiektu komputera w dół poprzez przesunięcie obiektu na planszy o określony wektor (-0.5f, 0.f).
 * Dodatkowo, funkcja obraca obiekt o kąt 180 stopni, aby był obrócony w odpowiednim kierunku.
 *
 * @param object Wskaźnik na obiekt komputera.
 */
void Game::m_down(Player* object)
{
    object->move(0.f, 0.5f);
    object->rotate_ob(180);
}


/**
 * @brief Aktualizuje obiekt gracza.
 *
 * Ta funkcja aktualizuje obiekt gracza na podstawie wciśniętych klawiszy. Odpowiada za poruszanie się gracza
 * w różnych kierunkach oraz obsługę strzałów gracza. Dodatkowo, sprawdza, czy gracz stracił wszystkie punkty
 * życia i ustawia flagę `endGame` w przypadku porażki.
 *
 * @param player Wskaźnik na obiekt gracza.
 */
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

/**
 * @brief Aktualizuje kolizje z cegłami.
 *
 * Ta funkcja sprawdza kolizje pomiędzy pociskami a cegłami. Jeśli wystąpi kolizja, usuwa odpowiednie
 * pociski i cegły z gry. Dodatkowo, zwiększa punktację gracza za trafienie cegły.
 *
 * @param object Wskaźnik na obiekt gracza.
 */
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

/**
 * @brief Sprawdza kolizje z cegłami.
 *
 * Ta funkcja sprawdza kolizje pomiędzy obiektem gracza a cegłami. Jeśli wystąpi kolizja,
 * dostosowuje pozycję gracza, aby uniknąć przenikania przez cegły.
 *
 * @param object Wskaźnik na obiekt gracza.
 */
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
                && playerbounds.top <= wallbounds.top + wallbounds.height
                && playerbounds.top + 26 >= wallbounds.top)
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

/**
 * @brief Sprawdza kolizje między dwoma graczami.
 *
 * Ta funkcja sprawdza kolizje pomiędzy dwoma graczami. Jeśli wystąpi kolizja,
 * dostosowuje pozycje graczy, aby uniknąć przenikania przez siebie.
 *
 * @param object Wskaźnik na obiekt pierwszego gracza.
 * @param object2 Wskaźnik na obiekt drugiego gracza.
 */
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

/**
 * @brief Sprawdza kolizje między graczem a flagą.
 *
 * Ta funkcja sprawdza kolizje między graczem a flagą. Jeśli wystąpi kolizja,
 * dostosowuje pozycje gracza, aby uniknąć przenikania przez flagę.
 *
 * @param object Wskaźnik na obiekt pierwszego gracza.
 * @param object2 Wskaźnik na obiekt flagi.
 */
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

/**
 * @brief Sprawdza kolizje między pociskami a graczem.
 *
 * Ta funkcja sprawdza kolizje między pociskami a graczem. Jeśli wystąpi kolizja,
 * usuwa pocisk, dodaje punkty dla gracza i zmniejsza jego punkty życia.
 *
 * @param object Wskaźnik na obiekt gracza.
 */
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
                && playerbounds.top <= wallbounds.top + 25
                && playerbounds.top + 25 >= wallbounds.top)
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
                && playerbounds.top <= wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >= wallbounds.top)
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

/**
 * @brief Sprawdza kolizje między pociskami a flagą.
 *
 * Ta funkcja sprawdza kolizje między pociskami a flagą. Jeśli wystąpi kolizja,
 * usuwa pocisk i zmniejsza  punkty życia obiektu flagi.
 *
 * @param object Wskaźnik na obiekt flagi.
 */
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
                && playerbounds.top <= wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >= wallbounds.top)
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

/**
 * @brief Sprawdza kolizje między pociskami a graczem botem.
 *
 * Ta funkcja sprawdza kolizje między pociskami a graczem botem. Jeśli wystąpi kolizja,
 * usuwa pocisk i zmniejsza punkty życia gracza bota.
 *
 * @param object Wskaźnik na obiekt gracza.
 * @param object2 Wskaźnik obiekt drugiego gracza.
 */
void Game::bulletcollisionSi(Player* object, Player* object2) // player bot
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

                cout << "\nhp: ";
                object->hp--;
                cout << object->hp << endl;
                licznik--;

                //  delete bullet;
            }


            //Right collision
            else if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top <= wallbounds.top + 25
                && playerbounds.top + 25 >= wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora

                cout << "\nhp: ";
                object->hp--;
                cout << object->hp << endl;
                licznik--;

                // delete bullet;

            }
            //Left collision
            else if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top <= wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >= wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora

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

/**
 * @brief Sprawdza kolizje między pociskami a graczem botem oraz aktualizuje punkty i statystyki gracza przeciwnika.
 *
 * Ta funkcja sprawdza kolizje między pociskami a graczem botem. Jeśli wystąpi kolizja,
 * usuwa pocisk, zmniejsza punkty życia gracza bota, zwiększa punkty i aktualizuje statystyki
 * gracza przeciwnika (object2).
 *
 * @param object Wskaźnik na obiekt gracza (bota).
 * @param object2 Wskaźnik na drugiego gracza (może być graczem lub graczem botem).
 */
void Game::bulletcollisionVsSi(Player* object, Player* object2)
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
                object2->points += 10;

                object->hp--;
                licznik--;

                object2->destroyedEnemies +=1;
                object2->numberOfEnemies -=1;

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
                object2->points += 10;
                object->hp--;
                licznik--;
                object2->destroyedEnemies += 1;
                object2->numberOfEnemies -= 1;
                //  delete bullet;
            }


            //Right collision
            else if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top <= wallbounds.top + 25
                && playerbounds.top + 25 >= wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object2->points += 10;
                object->hp--;
                licznik--;
                object2->destroyedEnemies += 1;
                object2->numberOfEnemies -= 1;
                // delete bullet;

            }
            //Left collision
            else if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top <= wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >= wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object2->points += 10;
                object->hp--;
                licznik--;
                object2->destroyedEnemies += 1;
                object2->numberOfEnemies -= 1;
                //delete bullet;

            }

        }
        licznik++;
    }

}

/**
 * @brief Sprawdza kolizje między pociskami a graczem oraz aktualizuje punkty i statystyki gracza przeciwnika.
 *
 * Ta funkcja sprawdza kolizje między pociskami a graczem. Jeśli wystąpi kolizja,
 * usuwa pocisk, zwiększa punkty gracza, zmniejsza punkty życia gracza przeciwnika (object2).
 *
 * @param object Wskaźnik na obiekt gracza.
 * @param object2 Wskaźnik na gracza przeciwnika.
 */
void Game::bulletcollisionVsEnemy(Player* object, Player* object2)
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

                object2->hp--;
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
                object2->hp--;
                licznik--;

                //  delete bullet;
            }


            //Right collision
            else if (playerbounds.left < wallbounds.left &&
                playerbounds.left + 25 < wallbounds.left + 25
                && playerbounds.top <= wallbounds.top + 25
                && playerbounds.top + 25 >= wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->points += 10;
                object2->hp--;
                licznik--;

                // delete bullet;

            }
            //Left collision
            else if (playerbounds.left > wallbounds.left &&
                playerbounds.left + 25 > wallbounds.left + wallbounds.width
                && playerbounds.top <= wallbounds.top + wallbounds.height
                && playerbounds.top + 25 >= wallbounds.top)
            {
                delete this->bullets.at(licznik); //Usuwa dynamicznie zaalokowaną pamięć pocisku o indeksie licznik w wektorze bullets
                this->bullets.erase(this->bullets.begin() + licznik); // usuwanie pocisku z wektora
                object->points += 10;
                object2->hp--;
                licznik--;

                //delete bullet;

            }

        }
        licznik++;
    }

}


/**
 * @brief Metoda aktualizująca pociski w grze.
 *
 * Metoda iteruje przez wektor pocisków, aktualizuje ich stan oraz sprawdza, czy znajdują się w granicach okna gry.
 * Jeśli pocisk opuścił granice ekranu, zostaje usunięty z wektora.
 */
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

/**
* @brief Metoda aktualizująca stan gry.
*
*
* Metoda odpowiedzialna za aktualizację stanu gry. Wywołuje inne metody aktualizacyjne, takie jak pollEvents(),
* updateBullets(), updateBricks(), updatePlayer(), updateGui(), updatePlayer(enemy), updateGui(enemy), bulletcollisionVsEnemy(),
* updateAllEnemies(), itp., w zależności od trybu gry (gracz kontra gracz lub gracz kontra boty). Aktualizuje również stan
* gracza i wroga. Metoda jest wywoływana w pętli głównej gry.
*/
void Game::update()
{
    this->pollEvents();
    this->updateBullets();
    
    this->player->update();
    this->bulletcollision(orzel);

    
    this->updateBricks(player);
    
    this->updatePlayer(player);

    this->Playerscollisions(player, orzel);

    if (!playervsbot)
    {  
        this->updateGui();
        this->updatePlayer(enemy);
        this->Playerscollisions(enemy, player);
        this->Playerscollisions(player, enemy);
        
        this->Playerscollisions(enemy, orzel);
       
         //this->updateGui(enemy);
        this->bulletcollisionVsEnemy(enemy, player);
        this->bulletcollisionVsEnemy(player, enemy);
        

        
        this->enemy->update();
        
        this->updateBricks(enemy);

    }
    else
    { 
        this->spawnEnemy();
        this->updateGuiVsBots();
        this->updateAllEnemies();
       
    }

    
    
       
    
}

/**
 * @brief Renderuje interfejs graficzny (GUI) gry na określonym celu.
 *
 * Ta funkcja rysuje elementy interfejsu GUI, w tym tekst gracza, tekst przeciwnika i tekst flagi,
 * na podanym celu renderowania.
 *
 * @param target Wskaźnik na cel renderowania SFML, na którym ma być renderowany interfejs GUI.
 */

void Game::renderGui(sf::RenderTarget* target)
{
    target->draw(this->guiTextPlayer);
    target->draw(this->guiTextEnemy);
    target->draw(this->guiTextFlag);

}

/**
 * @brief Renderuje interfejs graficzny (GUI) związany z botami gry na określonym celu.
 *
 * Ta funkcja rysuje elementy interfejsu GUI związane z botami, takie jak tekst gracza, tekst botów i tekst flagi,
 * na podanym celu renderowania.
 *
 * @param target Wskaźnik na cel renderowania SFML, na którym ma być renderowany interfejs GUI związany z botami.
 */

void Game::renderGuiBots(sf::RenderTarget* target)
{
    target->draw(this->guiTextPlayer);
    target->draw(this->guiTextBots);
    target->draw(this->guiTextFlag);
}

/**
 * @brief Renderuje komputerów na ekranie gry.
 *
 * Ta funkcja renderuje wszystkich wrogów znajdujących się w wektorze `enemies`
 * poprzez wywołanie metody `render` na każdym z nich i przekazanie wskaźnika na obiekt `window`
 * jako parametr.
 *
 */

void Game::renderEnemies()
{
    for (auto* bot : this->enemies) //Dla każdego obiektu w wektorze
    {
        bot->render(*this->window); //Wyswietla każdy obiekt na ekranie
    }

}

/**
 * @brief Renderuje wszystkie obiekty i interfejs gry na ekranie.
 *
 * Ta funkcja odpowiedzialna jest za renderowanie wszystkich obiektów gry, takich jak cegły, pociski, orzeł, gracz,
 * obiekty przeciwników oraz interfejs użytkownika. Wykonuje ona również czyszczenie okna gry i wyświetlanie informacji
 * o zakończeniu rozgrywki w przypadku ustawionej flagi `endGame`.
 *
 */

void Game::render()
{
    this->window->clear(); //czysci okno gry
    
   
   

    for (auto* bricks : this->bricks) //Dla każdego obiektu w wektorze
    {
        bricks->render(*this->window); //Wyswietla każdy obiekt na ekranie
    }

    for (auto* bullet : this->bullets) //Dla każdego obiektu w wektorze
    {
        bullet->render(this->window); //Wyswietla każdy obiekt na ekranie
    }



    
         
    this->orzel->render(*this->window);
    this->player->render(*this->window); //Rysuje obiekt gracza na ekranie


    //Wyswietlenie informacji o zakonczeniu rozgrywki
    if (this->endGame == true)
    {
        this->window->draw(this->endGameText);
    }

    if (!playervsbot)
    {
        this->renderGui(this->window);
        this->enemy->render(*this->window); //Wyswietlenie obiektu przeciwnika
        enemy->color_change(); //Zmiana koloru obiektu przeciwnika
    }
    else
    {
        player->color_change();
        this->renderGuiBots(this->window);
        this->renderEnemies();

    }

    this->window->display(); //Wyswietla na ekranie obecnie narysowane obiekty

}

/**
 * @brief Resetuje stan gry do ustawień początkowych.
 *
 * Ta funkcja przywraca ustawienia początkowe dla przeciwnika, flagi, gracza oraz innych elementów gry.
 * Przywraca pozycje, punkty, i punkty życia dla przeciwnika, gracza oraz botów.
 * Usuwa cegły, pociski i boty z gry. Przywraca pozycję flagi.
 * Resetuje flagę oznaczającą zakończenie gry.
 */
void Game::resetGame()
{
    //Przywrocenie ustawien poczatkowych przeciwnika
    this->enemy->setPosition(175.f, 25.f);
    this->enemy->points = 0;
    this->enemy->hp = 10;


    //Przywrocenie ustawien poczatkowych flagi
    this->orzel->destructionHp = 5;



    //Przywrocenie ustawien poczatkowych gracza
    this->player->setPosition(700.f, 450.f);
    this->player->points = 0;
    this->player->hp = 10;


    float pos_x = 50.f;
    float pos_y = 30.f;
    // Przywrocenie ustawien poczatkowych przeciwnika
    for (auto* bot : enemies)
    {
        bot->hp = 3;
        // Ustawienie pozycji dla każdego obiektu gracza
        bot->setPosition(pos_x, pos_y);
        pos_x += 50.f;
        pos_y += 50.f;
    }

    // Przywróć cegły do początkowego stanu
    for (auto* brick : bricks)
    {
        delete brick;
    }
    bricks.clear();
    stworzCegly();

    // Usuń pociski
    for (auto* bullet : bullets)
    {
        delete bullet;
    }
    bullets.clear();

    // Usuń boty
    for (auto* bot : enemies)
    {
        delete bot;
    }
    enemies.clear();

    // Zresetuj flagę
    this->orzel->setPosition(450.f, 550.f);

    // Zresetuj tekst końca gry
    this->endGame = false;

    player->points = 0;
    player->hp = 10;
    enemy->points = 0;
    enemy->hp = 10;
    this->player->numberOfEnemies = 5;
    this->player->destroyedEnemies = 0;
    this->guiTextPlayer.setPosition(0.f, 0.f);
    player->resetTexture();
}
