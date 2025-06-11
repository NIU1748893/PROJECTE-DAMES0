#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
#include <iostream>
#define SDL_MAIN_HANDLED
#include <windows.h>
#include "libreria.h"
#include "NFont.h"
#include <conio.h>
#endif

#include "joc.hpp"
#include "GraphicManager.h"

int main(int argc, const char* argv[])
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    pantalla.show();

    Joc joc;
    joc.inicialitza(MODE_JOC_NORMAL, "data/tauler.txt", "data/moviments.txt");

    do {
        pantalla.processEvents();
        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();

        bool final = joc.actualitza(mousePosX, mousePosY, mouseStatus);
        pantalla.update();
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

    joc.finalitza();
    SDL_Quit();
    return 0;
}