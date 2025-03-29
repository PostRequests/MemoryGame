#include "GameMem.h"
#include "Struct.h"
#include "menu/menu.h"
#include "console/console.h"

#include <iostream>
#include <ctime>
#include <Windows.h>
#include <ctime> 

void playMenu();
void playGame(Menu& menu);

int main()
{
    srand(time(0));
    system("chcp 1251>nul");
    FullScreenMode();
    Coordinate CS = getConsoleSize();
    drawLogo({ CS.x/2 - 6 * cWidth / 2, 1 });
    while (true)
    {
        playMenu();
    }
   
}

