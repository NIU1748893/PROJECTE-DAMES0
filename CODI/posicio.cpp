#include "Posicio.h"

Posicio::Posicio() : fila(0), columna(0) {}

Posicio::Posicio(const std::string& pos) {
    columna = pos[0] - 'a';
    fila = 8 - (pos[1] - '0');
}

int Posicio::getFila() const { return fila; }
int Posicio::getColumna() const { return columna; }

std::string Posicio::toString() const {
    return std::string(1, 'a' + columna) + std::to_string(8 - fila);
}

bool Posicio::operator==(const Posicio& other) const {
    return fila == other.fila && columna == other.columna;
}
