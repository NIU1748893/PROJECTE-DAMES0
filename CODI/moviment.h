#pragma once
#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <vector>
#include "Posicio.h"

class Moviment {
private:
    std::vector<Posicio> cami;
    std::vector<Posicio> pecesCapturades;

public:
    Moviment();

    void afegeixPosicio(const Posicio& p);
    void afegeixCaptura(const Posicio& p);
    const std::vector<Posicio>& getCami() const;
    const std::vector<Posicio>& getCaptures() const;
    bool haCapturat() const;
};

#endif
