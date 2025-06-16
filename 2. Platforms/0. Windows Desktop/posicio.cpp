#include "posicio.hpp"
#include <algorithm>
#include <cmath>
using namespace std;

//constructors
Posicio::Posicio() : m_fila(-1), m_columna(-1) {}

Posicio::Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}

Posicio::Posicio(const string& notacioEscacs)
{
    fromString(notacioEscacs);
}

//setters amb validació
bool Posicio::setFila(int fila)
{
    if (fila >= 0 && fila < N_FILES)
    {
        m_fila = fila;
        return true;
    }
    return false;
}

bool Posicio::setColumna(int columna)
{
    if (columna >= 0 && columna < N_COLUMNES)
    {
        m_columna = columna;
        return true;
    }
    return false;
}

bool Posicio::setPosicio(int fila, int columna)
{
    if (esPosicioValida(fila, columna))
    {
        m_fila = fila;
        m_columna = columna;
        return true;
    }
    return false;
}

//metodes de conversió
string Posicio::toString() const
{
    if (!esValida())
        return "??";

    string resultat = "a1";
    resultat[0] = 'a' + m_columna;
    resultat[1] = '1' + m_fila;
    return resultat;
}

void Posicio::fromString(const string& notacioEscacs)
{
    if (notacioEscacs.length() >= 2)
    {
        char columnaChar = tolower(notacioEscacs[0]);
        char filaChar = notacioEscacs[1];

        if (columnaChar >= 'a' && columnaChar <= 'h' && filaChar >= '1' && filaChar <= '8')
        {
            m_columna = columnaChar - 'a';
            m_fila = filaChar - '1';
        }
        else
        {
            m_fila = -1;
            m_columna = -1;
        }
    }
    else
    {
        m_fila = -1;
        m_columna = -1;
    }
}

//valids¿?
bool Posicio::esValida() const
{
    return esPosicioValida(m_fila, m_columna);
}

bool Posicio::esPosicioValida(int fila, int columna)
{
    return fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES;
}

// Utilitats per moviments
Posicio Posicio::getVei(int deltaFila, int deltaColumna) const
{
    return Posicio(m_fila + deltaFila, m_columna + deltaColumna);
}

bool Posicio::esDiagonalA(const Posicio& altra) const
{
    int deltaFila = abs(m_fila - altra.m_fila);
    int deltaColumna = abs(m_columna - altra.m_columna);
    return deltaFila == deltaColumna && deltaFila > 0;
}

bool Posicio::operator==(const Posicio& altra) const
{
    return m_fila == altra.m_fila && m_columna == altra.m_columna;
}

bool Posicio::operator!=(const Posicio& altra) const
{
    return !(*this == altra);
}

ostream& operator<<(ostream& os, const Posicio& pos)
{
    os << pos.toString();
    return os;
}

istream& operator>>(istream& is, Posicio& pos)
{
    string posStr;
    is >> posStr;
    pos.fromString(posStr);
    return is;
}

ifstream& operator>>(ifstream& fitxer, Posicio& pos)
{
    string posStr;
    fitxer >> posStr;
    pos.fromString(posStr);
    return fitxer;
}