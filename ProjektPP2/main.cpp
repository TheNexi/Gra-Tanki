/**
 * @file main.cpp
 * @brief Plik zrodlowy glowny main
 */

#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Menu.h"
#include <time.h>


 /**
  * @brief Główna funkcja programu.
  *
  * Funkcja `main` jest punktem wejścia do programu. Inicjuje ona grę, wywołuje funkcję renderowania menu gry,
  * a następnie uruchamia pętlę gry lub powraca do menu w zależności od decyzji gracza.
  *
  * @return Wartość 0 po zakończeniu programu.
  */
int main()
{
    srand(time(NULL));
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