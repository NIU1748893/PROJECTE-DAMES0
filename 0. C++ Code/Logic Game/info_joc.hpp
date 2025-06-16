#ifndef INFO_JOC_H
#define INFO_JOC_H

//posicio tauler pantalla
const int POS_X_TAULER = 75;
const int POS_Y_TAULER = 10;

//posicio primera casella respecte a cantonada superior esquerra
const int CASELLA_INICIAL_X = 52;
const int CASELLA_INICIAL_Y = 67;

//tamany caselles de tauler
const int AMPLADA_CASELLA = 62;
const int ALCADA_CASELLA = 62;

const int NUM_COLS_TAULER = 8;
const int NUM_FILES_TAULER = 8;

const int TAMANY_PANTALLA_X = 750;
const int TAMANY_PANTALLA_Y = 850;

typedef enum 
{
    MODE_JOC_NORMAL,
    MODE_JOC_REPLAY,
    MODE_JOC_NONE
} ModeJoc;

#endif 
