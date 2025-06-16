#ifndef FITXA_HPP
#define FITXA_HPP

#include <vector>
#include <string>
#include <iostream>
#include "posicio.hpp"
#include "moviment.hpp"
#include "const.hpp"
using namespace std;


typedef enum {
    FITXA_BUIDA,
    FITXA_NORMAL,
    FITXA_DAMA
}TipusFitxa;

typedef enum {
    COLOR_BLANC,
    COLOR_NEGRE
}ColorFitxa;

class Fitxa
{
private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Posicio m_ubicacio;
    vector<Moviment> m_movimentsPossibles;

public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color);
    Fitxa(TipusFitxa tipus, ColorFitxa color, const Posicio& pos);
    ~Fitxa() = default;

    TipusFitxa getTipus() const { return m_tipus; }
    ColorFitxa getColor() const { return m_color; }
    Posicio getUbicacio() const { return m_ubicacio; }
    int getNumMoviments() const { return static_cast<int>(m_movimentsPossibles.size()); }

    void setTipus(TipusFitxa tipus) { m_tipus = tipus; }
    void setColor(ColorFitxa color) { m_color = color; }
    void setUbicacio(const Posicio& pos) { m_ubicacio = pos; }

    //gestionar moviments
    void afegeixMoviment(const Moviment& moviment);
    void netejaMoviments();
    const vector<Moviment>& getMoviments() const;
    bool teMovimentsDisponibles() const;

    //op. especils
    void promocionarADama();
    bool esDama() const { return m_tipus == FITXA_DAMA; }
    bool esBuida() const { return m_tipus == FITXA_BUIDA; }
    bool esFitxaJugador() const { return m_tipus != FITXA_BUIDA; }

    char getCaracter() const;
    string toString() const;
    bool esColorContrari(const Fitxa& altra) const;
    bool potMoverse() const;

};

istream& operator>>(istream& input, Fitxa& fitxa);

#endif