#include "Fitxa.h"

Fitxa::Fitxa() : tipus(TIPUS_EMPTY), color(COLOR_BLANC) {}

Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color) : tipus(tipus), color(color) {}

TipusFitxa Fitxa::getTipus() const { return tipus; }
ColorFitxa Fitxa::getColor() const { return color; }

void Fitxa::setTipus(TipusFitxa t) { tipus = t; }
void Fitxa::setColor(ColorFitxa c) { color = c; }

void Fitxa::afegeixMoviment(const Moviment& m) {
    movimentsValids.push_back(m);
}

void Fitxa::netejaMoviments() {
    movimentsValids.clear();
}

const vector<Moviment>& Fitxa::getMovimentsValids() const {
    return movimentsValids;
}

bool Fitxa::esBuida() const {
    return tipus == TIPUS_EMPTY;
}

void Fitxa::convertirADama() {
    if (tipus == TIPUS_NORMAL) {
        tipus = TIPUS_DAMA;
    }
}