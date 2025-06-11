#ifndef JOC_HPP
#define JOC_HPP

#include <vector>
#include <string>
#include "info_joc.hpp"
#include "Posicio.h"
#include "Fitxa.h"
#include "tauler.h"

class Joc
{
public:
    Joc();
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void inicialitza(ModeJoc mode, const std::string& nomFitxerTauler, const std::string& nomFitxerMoviments);
    void finalitza();
    void processaClick(int mousePosX, int mousePosY);
    bool esMovimentValid(const Posicio& desti) const;
    void canviaTorn();
    void visualitza() const;

private:
    Tauler m_tauler;
    ModeJoc m_mode;
    ColorFitxa m_torn;
    bool m_finalitzat;
    Posicio m_seleccionada;
    std::vector<Posicio> m_movimentsValids;
    std::string m_fitxerMoviments;
};

#endif