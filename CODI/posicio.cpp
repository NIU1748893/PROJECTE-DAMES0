#include "Posicio.h"
#include <iostream>
using namespace std;

Posicio::Posicio() : fila(0), columna(0) {}

Posicio::Posicio(const string& pos)
{
    columna = pos[0] - 'a';
    fila = 8 - (pos[1] - '0');
}

int Posicio::getFila() const { return fila; }
int Posicio::getColumna() const { return columna; }

string Posicio::toString() const {
    return string(1, 'a' + columna) + to_string(8 - fila);
}

bool Posicio::operator==(const Posicio& other) const {
    return fila == other.fila && columna == other.columna;
}

ostream& operator<<(ostream& os, const Posicio& pos) {
    os << pos.toString();
    return os;
}