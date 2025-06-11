#include "Posicio.h"
#include <iostream>

using namespace std;

Posicio::Posicio() : fila(0), columna(0) {}

Posicio::Posicio(const std::string& pos)
{
    columna = pos[0] - 'a';
    fila = 8 - (pos[1] - '0');
}

Posicio::Posicio(int fila, int columna) : fila(fila), columna(columna) {}

int Posicio::getFila() const { return fila; }
int Posicio::getColumna() const { return columna; }

string Posicio::toString() const {
    return std::string(1, 'a' + columna) + std::to_string(8 - fila);
}

bool Posicio::operator==(const Posicio& other) const {
    return fila == other.fila && columna == other.columna;
}

ostream& operator<<(std::ostream& os, const Posicio& pos) {
    os << pos.toString();
    return os;
}