#include <iostream>
#include "Game.h"
#include "Player.h"
#include <time.h>



int main()
{
    srand(time(NULL));
    //srand(time(static_cast<unsigned>(0))); // seed for time losowa liczba
    //Inicjacja Gry

    Game game;
    
    //Petla gry
 

    

    game.run();
          
    //Petla gry koniec
  
    return 0;
}