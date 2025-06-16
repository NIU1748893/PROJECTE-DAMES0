#include <iostream>
#include <string>

// Para Windows - SDL
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)
#define SDL_MAIN_HANDLED
#include <windows.h>
#endif

#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include "joc.hpp"
#include "info_joc.hpp"

using namespace std;

// Funciones auxiliares
ModeJoc seleccionarMode();
string obtenirNomFitxer(const string& tipus);

int main(int argc, const char* argv[])
{
    cout << "----------------------------------------------------" << endl;
    cout << "  .-.-.-. BENVINGUT AL JOC DE LES DAMES!! .-.-.-." << endl;
    cout << "----------------------------------------------------" << endl;

    // Configuración inicial por consola
    ModeJoc mode = seleccionarMode();
    if (mode == MODE_JOC_NONE) {
        return 0;
    }

    string fitxerTauler = obtenirNomFitxer("tauler inicial");
    string fitxerMoviments = obtenirNomFitxer("moviments");

    cout << "\nCARREGANT TAULER..." << endl;
    cout << endl;

    // Inicializar SDL
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    // Crear pantalla
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    pantalla.show();

    // Crear y configurar juego
    Joc joc;
    joc.inicialitza(mode, fitxerTauler, fitxerMoviments);

    cout << "Partida iniciada! Utilitza el ratoli per interactuar amb les fitxes i el tauler" << endl;
    cout << "Prem ESC per sortir." << endl;

    // Bucle principal del juego
    bool partidaAcabada = false;
    do
    {
        // Capturar eventos
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();

        // Actualizar juego
        partidaAcabada = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        // Actualizar pantalla
        pantalla.update();

        if (partidaAcabada)
            cout << "PARTIDA FINALITZADA!!" << endl;

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !partidaAcabada);

    // Finalizar
    joc.finalitza();
    SDL_Quit();

    cout << "BEN JUGAT" << endl;
    return 0;
}

ModeJoc seleccionarMode()
{
    int opcio;

    do
    {
        cout << "   ===> SELECCIONA UN MODE DE JOC <===" << endl;
        cout << "       1. Partida Normal" << endl;
        cout << "       2. Reproduir Partida (Replay)" << endl;
        cout << "       3. Sortir" << endl;
        cout << "    Introdueix la teva opcio (1-3): ";
        cin >> opcio;
        cout << endl;

        switch (opcio)
        {
        case 1:
            return MODE_JOC_NORMAL;
        case 2:
            return MODE_JOC_REPLAY;
        case 3:
            return MODE_JOC_NONE;
        default:
            cout << "ERROR: Opcio no valida." << endl;
            cout << endl;
            break;
        }
    } while (opcio < 1 || opcio > 3);

    return MODE_JOC_NONE;
}

string obtenirNomFitxer(const string& tipus)
{
    string nomFitxer;

    cout << "Introdueix el nom del fitxer per " << tipus << endl;
    cout << "(Presiona INTRO per utilitzar fitxer per defecte): ";
    cin.ignore();
    cout << endl;
    getline(cin, nomFitxer);

    if (nomFitxer.empty())
    {
        if (tipus.find("tauler") != string::npos)
            nomFitxer = "tauler_inicial.txt";  
        else
            nomFitxer = "moviments.txt";
    }

    if (nomFitxer.find(".txt") == string::npos)
        nomFitxer += ".txt";

    nomFitxer = "../../1. Resources/MP_Practica.tlog/data/Games/" + nomFitxer;

    cout << "Utilitzant fitxer: " << nomFitxer << endl;
    cout << endl;
    return nomFitxer;
}