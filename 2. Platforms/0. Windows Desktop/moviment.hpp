#ifndef MOVIMENT_HPP
#define MOVIMENT_HPP

#include <vector>
#include <string>
#include "posicio.hpp"
#include "const.hpp"
using namespace std;

//forwarddeclaration para evitar dependencia circular
class Fitxa;

class Moviment
{
private:
    vector<Posicio> m_posicions;
    vector<Posicio> m_captures;  //fitxes capturades durant moviment

public:
    Moviment();
    Moviment(const Posicio& posicioInicial);
    ~Moviment() = default;

    Posicio getPosicioInicial() const;
    Posicio getPosicioFinal() const;
    Posicio getPosicioActual() const;
    int getNumPosicions() const { return static_cast<int>(m_posicions.size()); }
    int getNumCaptures() const { return static_cast<int>(m_captures.size()); }
    const vector<Posicio>& getCaptures() const { return m_captures; }

    //gestio posicions
    void afegeixPosicio(const Posicio& pos);
    bool getPosicions(int& numPosicions, Posicio posicions[]) const;

    //gestio captures
    void afegeixCaptura(const Posicio& pos);

    //validacions:)
    bool esMovimentValid() const;
    bool esMovimentSimple() const;
    bool esMovimentAmbCaptura() const { return !m_captures.empty(); }

    //representacio en string
    string toString() const;

    bool operator==(const Moviment& altre) const;
};

#endif