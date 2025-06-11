#pragma once
#ifndef TAULER_H
#define TAULER_H

#include "Fitxa.h"
#include "Posicio.h"
#include <vector>

class Tauler
{
private:
    static const int N_FILES = 8;
    static const int N_COLUMNES = 8;
    Fitxa* m_tauler[N_FILES][N_COLUMNES];

    void netejaTauler();

public:
    Tauler();
    ~Tauler();
    void inicialitza(const std::string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    std::string toString() const;
    void visualitza() const;
    Fitxa* getFitxa(int fila, int columna) const;
};

#endif