#pragma once
#ifndef POSICIO_H
#define POSICIO_H
#include <string>
#include <iostream>  
using namespace std;

class Posicio
{
private:
    int fila;   // 0 a 7 (fila 8 �s 0, fila 1 �s 7)
    int columna; // 0 a 7 (a �s 0, h �s 7)

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