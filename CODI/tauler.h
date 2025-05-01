#pragma once
#ifndef TAULER_H
#define TAULER_H

#include "Fitxa.h"
#include "Posicio.h"
#include <string>
using namespace std;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Tauler
{
private:
    Fitxa m_tauler[N_FILES][N_COLUMNES];

public:
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    string toString() const;
};

#endif