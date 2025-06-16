#ifndef POSICIO_HPP
#define POSICIO_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "const.hpp"

using namespace std;

class Posicio
{
private:
    int m_fila;
    int m_columna;

public:
    Posicio();
    Posicio(int fila, int columna);
    Posicio(const string& notacioEscacs);

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }

    bool setFila(int fila);
    bool setColumna(int columna);
    bool setPosicio(int fila, int columna);

    string toString() const;
    void fromString(const string& notacioEscacs);

    bool esValida() const;
    static bool esPosicioValida(int fila, int columna);

    Posicio getVei(int deltaFila, int deltaColumna) const;
    bool esDiagonalA(const Posicio& altra) const;

    bool operator==(const Posicio& altra) const;
    bool operator!=(const Posicio& altra) const;
};

ostream& operator<<(ostream& os, const Posicio& pos);
istream& operator>>(istream& is, Posicio& pos);
ifstream& operator>>(ifstream& fitxer, Posicio& pos);

#endif // POSICIO_HPP