#include <iostream>
#include "Game.h"


int main()
{
    //Inicjacja Gry

    Game game;

    //Petla gry

    while (game.running())
    {
        //Update
        game.update();
        
        //Render
        game.render();

     }
          
    //Petla gry koniec
  
    return 0;
}