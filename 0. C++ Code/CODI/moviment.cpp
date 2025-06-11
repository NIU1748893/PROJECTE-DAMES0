#include "Moviment.h"
using namespace std;

Moviment::Moviment() {}

void Moviment::afegeixPosicio(const Posicio& p) {
    cami.push_back(p);
}

void Moviment::afegeixCaptura(const Posicio& p) {
    pecesCapturades.push_back(p);
}

const vector<Posicio>& Moviment::getCami() const {
    return cami;
}

const vector<Posicio>& Moviment::getCaptures() const {
    return pecesCapturades;
}

bool Moviment::haCapturat() const {
    return !pecesCapturades.empty();
}