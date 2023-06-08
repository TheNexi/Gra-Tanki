#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Menu.h"
#include <time.h>



int main()
{
    srand(time(NULL));
    //srand(time(static_cast<unsigned>(0))); // seed for time losowa liczba
    //Inicjacja Gry

    Game game;
    
 

    //Petla gry
    game.renderMenu();
    
    if (game.shouldReturnToMenu())
    {
        game.resetGame();
        game.renderMenu();
    }
    else
    {
        game.run();
    }
  
          
    //Petla gry koniec
  
    return 0;
}