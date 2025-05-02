#pragma once
#ifndef POSICIO_H
#define POSICIO_H
#include <string>
#include <iostream>  
using namespace std;

class Posicio
{
private:
    int fila;   // 0 a 7 (fila 8 és 0, fila 1 és 7)
    int columna; // 0 a 7 (a és 0, h és 7)

public:
    Posicio(); // constructor buit
    Posicio(const string& pos);
    Posicio(int fila, int columna) : fila(fila), columna(columna) {}


    int getFila() const;
    int getColumna() const;
    string toString() const;

    bool operator==(const Posicio& other) const;
};

ostream& operator<<(ostream& os, const Posicio& pos);

#endif