#pragma once
#ifndef POSICIO_H
#define POSICIO_H

#include <string>
#include <iostream>

class Posicio
{
private:
    int fila;
    int columna;

public:
    Posicio();
    Posicio(const std::string& pos);
    Posicio(int fila, int columna);

    int getFila() const;
    int getColumna() const;
    std::string toString() const;
    bool operator==(const Posicio& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Posicio& pos);
};

#endif