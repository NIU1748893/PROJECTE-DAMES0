#ifndef JOC_HPP
#define JOC_HPP

#include <string>
#include <vector>
#include "info_joc.hpp"
#include "tauler.hpp"
#include "CuaMoviments.hpp"
#include "fitxa.hpp"
#include "GraphicManager.h"
using namespace std;

class Joc
{
private:
    Tauler m_tauler;
    CuaMoviments m_cua;
    ModeJoc m_modeJoc;

    string m_fitxerTauler;
    string m_fitxerMoviments;

    //estat de partida
    ColorFitxa m_jugadorActual;
    bool m_partidaAcabada;
    ColorFitxa m_guanyador;

    //gestio de selecc i movi
    bool m_fitxaSeleccionada;
    Posicio m_posicioSeleccionada;
    vector<Posicio> m_posicionsValides;

    //control interaccio
    bool m_mouseAnterior;

    //per replay
    int m_tempsUltimMoviment;

    //Stats de partida
    int m_fitxesBlanquesMortes;
    int m_fitxesNegresMortes;

public:
    Joc();
    ~Joc() = default;

    void inicialitza(ModeJoc mode, const std::string& nomFitxerTauler, const std::string& nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void finalitza();

private:
    //auxiliars per gestionar joc
    void inicialitzaModusNormal();
    void inicialitzaModusReplay();
    bool actualitzaModusNormal(int mousePosX, int mousePosY, bool mouseStatus);
    bool actualitzaModusReplay(int mousePosX, int mousePosY, bool mouseStatus);

    //interactuar amb mouse
    Posicio converteixCoordenadesMouseATauler(int mousePosX, int mousePosY);
    bool estaDinsLimitsTauler(int mousePosX, int mousePosY);
    void seleccionaFitxa(const Posicio& pos);
    void executaMoviment(const Posicio& desti);
    bool esPosicioValida(const Posicio& pos);

    //gestio torns i final de partida
    void canviaTorn();
    bool comprovaFinalPartida();
    ColorFitxa getGuanyador();

    //dibuix
    void dibuixaFons();
    void dibuixaTauler();
    void dibuixaFitxes();
    void dibuixaPosicionsPossibles();
    void dibuixaInformacioPartida();
    void dibuixaPantallaFinal();

    bool esFitxaDelJugadorActual(const Posicio& pos);
    IMAGE_NAME obteImatgeFitxa(const Fitxa& fitxa);
    string getStringColor(ColorFitxa color);
    string getStringModeJoc();
};

#endif