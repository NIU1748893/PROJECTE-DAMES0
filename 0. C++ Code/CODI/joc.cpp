#include "joc.hpp"
#include "tauler.h"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"

Joc::Joc() : m_mode(MODE_JOC_NONE), m_torn(COLOR_BLANC), m_finalitzat(false) {}

void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments) {
    m_mode = mode;
    m_fitxerMoviments = nomFitxerMoviments;
    m_torn = COLOR_BLANC;
    m_finalitzat = false;
    m_seleccionada = Posicio();
    m_movimentsValids.clear();

    m_tauler.inicialitza(nomFitxerTauler);
    m_tauler.actualitzaMovimentsValids();
}

void Joc::finalitza() {
    if (m_mode == MODE_JOC_NORMAL) {
        // Guardar movimientos si es necesario
    }
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus) {
    visualitza();

    if (m_finalitzat) {
        string msg = "Partida finalitzada. Guanyador: ";
        msg += (m_torn == COLOR_BLANC) ? "Negres" : "Blanques";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 50, 700, 1.0, msg);
        return true;
    }

    if (mouseStatus) {
        processaClick(mousePosX, mousePosY);
    }

    return false;
}

void Joc::visualitza() const {
    // Dibujar fondo y tablero
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    // Dibujar fichas
    m_tauler.visualitza();

    // Mostrar turno actual
    string torn = (m_torn == COLOR_BLANC) ? "Blanques" : "Negres";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 50, 650, 1.0, "Torn: " + torn);

    // Mostrar posiciones válidas
    for (const Posicio& p : m_movimentsValids) {
        int posX = POS_X_TAULER + CASELLA_INICIAL_X + (p.getColumna() * AMPLADA_CASELLA);
        int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (p.getFila() * ALCADA_CASELLA);
        GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
    }
}

void Joc::processaClick(int mousePosX, int mousePosY) {
    // Verificar si el click está dentro del tablero
    if (mousePosX >= POS_X_TAULER + CASELLA_INICIAL_X &&
        mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y &&
        mousePosX <= POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER &&
        mousePosY <= POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER) {

        int col = (mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X)) / AMPLADA_CASELLA;
        int fila = (mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y)) / ALCADA_CASELLA;
        Posicio pos(fila, col);

        Fitxa* fitxa = m_tauler.getFitxa(fila, col);

        // Si no hay ficha seleccionada y se clica una ficha del color del turno actual
        if (m_seleccionada == Posicio() && fitxa != nullptr && fitxa->getColor() == m_torn) {
            m_seleccionada = pos;
            int nPosicions;
            Posicio posicionsPossibles[8];
            m_tauler.getPosicionsPossibles(m_seleccionada, nPosicions, posicionsPossibles);
            m_movimentsValids.clear();
            for (int i = 0; i < nPosicions; i++) {
                m_movimentsValids.push_back(posicionsPossibles[i]);
            }
        }
        // Si hay ficha seleccionada y se clica una posición válida
        else if (!(m_seleccionada == Posicio()) && esMovimentValid(pos)) {
            m_tauler.mouFitxa(m_seleccionada, pos);
            m_seleccionada = Posicio();
            m_movimentsValids.clear();
            canviaTorn();
        }
        // Si se clica otra ficha del mismo color
        else if (fitxa != nullptr && fitxa->getColor() == m_torn) {
            m_seleccionada = pos;
            int nPosicions;
            Posicio posicionsPossibles[8];
            m_tauler.getPosicionsPossibles(m_seleccionada, nPosicions, posicionsPossibles);
            m_movimentsValids.clear();
            for (int i = 0; i < nPosicions; i++) {
                m_movimentsValids.push_back(posicionsPossibles[i]);
            }
        }
    }
}

bool Joc::esMovimentValid(const Posicio& desti) const {
    for (const Posicio& p : m_movimentsValids) {
        if (p == desti) {
            return true;
        }
    }
    return false;
}

void Joc::canviaTorn() {
    m_torn = (m_torn == COLOR_BLANC) ? COLOR_NEGRE : COLOR_BLANC;
    m_tauler.actualitzaMovimentsValids();

    bool potMoure = false;
    for (int fila = 0; fila < N_FILES && !potMoure; fila++) {
        for (int col = 0; col < N_COLUMNES && !potMoure; col++) {
            Fitxa* fitxa = m_tauler.getFitxa(fila, col);
            if (fitxa != nullptr && !fitxa->esBuida() && fitxa->getColor() == m_torn) {
                int nPosicions;
                Posicio posicionsPossibles[8];
                m_tauler.getPosicionsPossibles(Posicio(fila, col), nPosicions, posicionsPossibles);
                if (nPosicions > 0) {
                    potMoure = true;
                }
            }
        }
    }

    if (!potMoure) {
        m_finalitzat = true;
    }
}