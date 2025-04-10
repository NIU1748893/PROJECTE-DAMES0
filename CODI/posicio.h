#pragma once
#ifndef POSICIO_H
#define POSICIO_H

#include <string>

class Posicio {
private:
    int fila;   // 0 a 7 (fila 8 �s 0, fila 1 �s 7)
    int columna; // 0 a 7 (a �s 0, h �s 7)

public:
    Posicio(); // constructor buit
    Posicio(const std::string& pos);

    int getFila() const;
    int getColumna() const;
    std::string toString() const;

    bool operator==(const Posicio& other) const;
};

#endif
