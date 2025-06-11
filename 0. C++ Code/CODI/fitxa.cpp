#include "Fitxa.h"
#include "GraphicManager.h"

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

const std::vector<Moviment>& Fitxa::getMovimentsValids() const {
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

void Fitxa::visualitza(int posX, int posY) const {
    if (!esBuida()) {
        IMAGE_NAME graf;
        if (tipus == TIPUS_NORMAL) {
            graf = (color == COLOR_BLANC) ? GRAFIC_FITXA_BLANCA : GRAFIC_FITXA_NEGRA;
        }
        else {
            graf = (color == COLOR_BLANC) ? GRAFIC_DAMA_BLANCA : GRAFIC_DAMA_NEGRA;
        }
        GraphicManager::getInstance()->drawSprite(graf, posX, posY);
    }
}