#include "Tauler.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Tauler::inicialitza(const std::string& nomFitxer) {
    // Inicialitzar tot buit
    for (int i = 0; i < N_FILES; ++i)
        for (int j = 0; j < N_COLUMNES; ++j)
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC);

    std::ifstream fitxer(nomFitxer);
    std::string linia;

    while (std::getline(fitxer, linia)) {
        std::istringstream iss(linia);
        char tipusChar;
        std::string pos;
        iss >> tipusChar >> pos;

        TipusFitxa tipus;
        ColorFitxa color;

        switch (tipusChar) {
        case 'O': tipus = TIPUS_NORMAL; color = COLOR_BLANC; break;
        case 'X': tipus = TIPUS_NORMAL; color = COLOR_NEGRE; break;
        case 'D': tipus = TIPUS_DAMA; color = COLOR_BLANC; break;
        case 'R': tipus = TIPUS_DAMA; color = COLOR_NEGRE; break;
        default: continue;
        }

        Posicio p(pos);
        m_tauler[p.getFila()][p.getColumna()] = Fitxa(tipus, color);
    }
}
