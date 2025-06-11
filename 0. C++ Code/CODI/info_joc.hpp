#ifndef INFO_JOC_HPP
#define INFO_JOC_HPP

// Posición del tablero en pantalla
const int POS_X_TAULER = 75;
const int POS_Y_TAULER = 10;

// Tamaño de las casillas
const int AMPLADA_CASELLA = 62;
const int ALCADA_CASELLA = 62;

// Tamaño de la pantalla
const int TAMANY_PANTALLA_X = 750;
const int TAMANY_PANTALLA_Y = 850;

enum ModeJoc {
    MODE_JOC_NORMAL,
    MODE_JOC_REPLAY,
    MODE_JOC_NONE
};

enum ColorFitxa {
    COLOR_NEGRE,
    COLOR_BLANC
};

#endif