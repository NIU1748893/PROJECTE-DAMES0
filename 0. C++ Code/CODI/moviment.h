#pragma once
#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <vector>
#include "Posicio.h"

using namespace std;

class Moviment
{
private:
    vector<Posicio> cami;
    vector<Posicio> pecesCapturades;

public:
    Moviment();

    void afegeixPosicio(const Posicio& p);
    void afegeixCaptura(const Posicio& p);
    const vector<Posicio>& getCami() const;
    const vector<Posicio>& getCaptures() const;
    bool haCapturat() const;
};

#endif