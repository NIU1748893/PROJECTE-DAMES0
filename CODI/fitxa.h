#pragma once
#ifndef FITXA_H
#define FITXA_H

#include <vector>
#include "Posicio.h"
#include "Moviment.h"

typedef enum { TIPUS_NORMAL, TIPUS_DAMA, TIPUS_EMPTY } TipusFitxa;
typedef enum { COLOR_NEGRE, COLOR_BLANC } ColorFitxa;

class Fitxa {
private:
    TipusFitxa tipus;
    ColorFitxa color;
    std::vector<Moviment> movimentsValids;

public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color);

    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    void setTipus(TipusFitxa t);
    void setColor(ColorFitxa c);
    void afegeixMoviment(const Moviment& m);
    void netejaMoviments();
    const std::vector<Moviment>& getMovimentsValids() const;

    bool esBuida() const;
    void convertirADama();
};

#endif
