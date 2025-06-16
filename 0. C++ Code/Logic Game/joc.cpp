#include "joc.hpp"
#include "GraphicManager.h"
#include <iostream>

Joc::Joc()
    : m_modeJoc(MODE_JOC_NONE)
    , m_jugadorActual(COLOR_BLANC)
    , m_partidaAcabada(false)
    , m_guanyador(COLOR_BLANC)
    , m_fitxaSeleccionada(false)
    , m_mouseAnterior(false)
    , m_tempsUltimMoviment(0)
    , m_fitxesBlanquesMortes(0)
    , m_fitxesNegresMortes(0)
{}

//inicialitza la partida segons el mode
void Joc::inicialitza(ModeJoc mode, const std::string& nomFitxerTauler, const std::string& nomFitxerMoviments)
{
    m_modeJoc = mode;
    m_fitxerTauler = nomFitxerTauler;
    m_fitxerMoviments = nomFitxerMoviments;

    //inicialitzem el tauler sempre
    if (!m_tauler.carregaPartidaDesArxiu(nomFitxerTauler))
    {
        cout << "ERROR: No es pot carregar el fitxer del tauler: " << nomFitxerTauler << endl;
        return;
    }

    m_tauler.actualitzaMovimentsValids();

    switch (mode)
    {
    case MODE_JOC_NORMAL:
        inicialitzaModusNormal();
        break;
    case MODE_JOC_REPLAY:
        inicialitzaModusReplay();
        break;
    default:
        cout << "ERROR: Mode de joc inexistent." << endl;
        break;
    }

    cout << "Partida inicialitzada en mode: " << getStringModeJoc() << endl;
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    dibuixaFons();
    dibuixaTauler();
    dibuixaFitxes();

    // Si hi ha una fitxa seleccionada, mostrem les posicions possibles
    if (m_fitxaSeleccionada)
        dibuixaPosicionsPossibles();

    // Dibuixem la informació de la partida
    dibuixaInformacioPartida();

    if (m_partidaAcabada)
    {
        dibuixaPantallaFinal();
        return true;
    }

    //actualitzem segons el mode
    bool partidaAcabada = false;
    switch (m_modeJoc)
    {
    case MODE_JOC_NORMAL:
        partidaAcabada = actualitzaModusNormal(mousePosX, mousePosY, mouseStatus);
        break;
    case MODE_JOC_REPLAY:
        partidaAcabada = actualitzaModusReplay(mousePosX, mousePosY, mouseStatus);
        break;
    default:
        break;
    }

    return partidaAcabada;
}

void Joc::finalitza()
{
    if (m_modeJoc == MODE_JOC_NORMAL)
    {
        if (m_cua.guardaMovimentsAFitxer(m_fitxerMoviments)) 
            cout << "Moviments guardats correctament a: " << m_fitxerMoviments << endl;
        else
            cout << "Error guardant moviments al fitxer: " << m_fitxerMoviments << endl;
    }

    cout << "Partida finalitzada." << endl;
}


void Joc::inicialitzaModusNormal()
{
    m_jugadorActual = COLOR_BLANC;
    m_partidaAcabada = false;
    m_fitxaSeleccionada = false;
    m_posicionsValides.clear();
    m_mouseAnterior = false;
}

void Joc::inicialitzaModusReplay()
{
    m_jugadorActual = COLOR_BLANC;
    m_partidaAcabada = false;
    m_fitxaSeleccionada = false;
    m_posicionsValides.clear();
    m_tempsUltimMoviment = 0;
    m_mouseAnterior = false;

    if (!m_cua.carregaMovimentsDeFitxer(m_fitxerMoviments))
    {
        cout << "ERROR: No s'ha pogut carregar el fitxer de moviments: " << m_fitxerMoviments << endl;
        m_partidaAcabada = true;
    }
    else
        cout << "Fitxer de moviments carregat correctament." << endl;
}

//actualitza mode normal amb interacció del mouse
bool Joc::actualitzaModusNormal(int mousePosX, int mousePosY, bool mouseStatus)
{
    //detectem click del mouse
    bool mouseClick = mouseStatus && !m_mouseAnterior;
    m_mouseAnterior = mouseStatus;

    if (mouseClick && estaDinsLimitsTauler(mousePosX, mousePosY))
    {
        Posicio posClick = converteixCoordenadesMouseATauler(mousePosX, mousePosY);

        if (!m_fitxaSeleccionada)
        {
            //intentem seleccionar una fitxa
            if (esFitxaDelJugadorActual(posClick))
                seleccionaFitxa(posClick);
        }
        else
        {
            //tenim una fitxa seleccionada
            if (posClick == m_posicioSeleccionada)
            {
                //deseleccionem la fitxa
                m_fitxaSeleccionada = false;
                m_posicionsValides.clear();
            }
            else if (esPosicioValida(posClick))
            {
                executaMoviment(posClick);

                if (comprovaFinalPartida())
                {
                    m_partidaAcabada = true;
                    m_guanyador = getGuanyador();
                    return true;
                }
            }
            else if (esFitxaDelJugadorActual(posClick))
                seleccionaFitxa(posClick);
            else
            {
                //click en posició no vàlida, deseleccionem
                m_fitxaSeleccionada = false;
                m_posicionsValides.clear();
            }
        }
    }

    return false;
}

//actualitza mode replay amb temporització
bool Joc::actualitzaModusReplay(int mousePosX, int mousePosY, bool mouseStatus)
{
    //reproduim moviments automàticament cada segon
    int tempsActual = SDL_GetTicks();

    if (tempsActual - m_tempsUltimMoviment > 1000)
    { // 1 segon entre moviments
        m_tempsUltimMoviment = tempsActual;

        if (!m_cua.esBuida())
        {
            Moviment moviment = m_cua.obteSeguentMoviment();

            Posicio origen = moviment.getPosicioInicial();
            Posicio desti = moviment.getPosicioFinal();

            //actualitzem el comptador de captures ABANS de moure
            const vector<Posicio>& captures = moviment.getCaptures();
            for (const Posicio& captura : captures)
            {
                const Fitxa& fitxaCapturada = m_tauler.getFitxa(captura);
                if (fitxaCapturada.getColor() == COLOR_BLANC)
                    m_fitxesBlanquesMortes++;
                else
                    m_fitxesNegresMortes++;
            }

            m_posicioSeleccionada = origen;
            m_fitxaSeleccionada = true;

            if (m_tauler.mouFitxa(origen, desti))
            {
                cout << "Moviment reproduit: " << origen << " -> " << desti << endl;

                //afegim a la cua per guardar al final si cal
                m_cua.afegeixMoviment(moviment);

                canviaTorn();
                m_fitxaSeleccionada = false;

                if (comprovaFinalPartida())
                {
                    m_partidaAcabada = true;
                    m_guanyador = getGuanyador();
                    return true;
                }
            }
        }
        else
        {
            cout << "No queden mes moviments a reproduir." << endl;
            m_partidaAcabada = true;
            return true;
        }
    }

    return false;
}

// metodes per dibuixar

void Joc::dibuixaFons()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
}

void Joc::dibuixaTauler()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
}

void Joc::dibuixaFitxes()
{
    for (int fila = 0; fila < N_FILES; fila++)
    {
        for (int col = 0; col < N_COLUMNES; col++)
        {
            const Fitxa& fitxa = m_tauler.getFitxa(fila, col);

            if (fitxa.esFitxaJugador())
            {
                float posX = static_cast<float>(POS_X_TAULER + CASELLA_INICIAL_X + col * AMPLADA_CASELLA);
                float posY = static_cast<float>(POS_Y_TAULER + CASELLA_INICIAL_Y + (N_FILES - 1 - fila) * ALCADA_CASELLA);

                IMAGE_NAME imatge = obteImatgeFitxa(fitxa);
                GraphicManager::getInstance()->drawSprite(imatge, posX, posY);
            }
        }
    }
}

void Joc::dibuixaPosicionsPossibles()
{
    for (const Posicio& pos : m_posicionsValides)
    {
        float posX = static_cast<float>(POS_X_TAULER + CASELLA_INICIAL_X + pos.getColumna() * AMPLADA_CASELLA);
        float posY = static_cast<float>(POS_Y_TAULER + CASELLA_INICIAL_Y + (N_FILES - 1 - pos.getFila()) * ALCADA_CASELLA);

        GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
    }
}

void Joc::dibuixaInformacioPartida()
{
    GraphicManager* gm = GraphicManager::getInstance();

    if (!m_partidaAcabada)
    {

        string torn = "TORN: ";
        gm->drawFont(FONT_WHITE_30, 560, 700, 0.8f, torn);

        //dibuixar fitxa del jugador actual
        IMAGE_NAME fitxaTorn;
        if (m_jugadorActual == COLOR_BLANC)
            fitxaTorn = GRAFIC_FITXA_BLANCA;
        else
            fitxaTorn = GRAFIC_FITXA_NEGRA;

        gm->drawSprite(fitxaTorn, 650, 690);

        

        //capturades
        gm->drawFont(FONT_WHITE_30, 50, 650, 0.8f, "CAPTURES:");

        //blanques capturades
        gm->drawFont(FONT_WHITE_30, 50, 680, 0.7f, "Blanques: " + to_string(m_fitxesBlanquesMortes));
        for (int i = 0; i < m_fitxesBlanquesMortes && i < 12; i++)
        {
            float x = 200.0f + (i % 6) * 30.0f;
            float y = 670.0f + (i / 6) * 30.0f;
            gm->drawSprite(GRAFIC_FITXA_BLANCA, x, y);
        }

        //negres capturades
        gm->drawFont(FONT_RED_30, 50, 730, 0.7f, "Negres: " + to_string(m_fitxesNegresMortes));
        for (int i = 0; i < m_fitxesNegresMortes && i < 12; i++)
        {
            float x = 200.0f + (i % 6) * 30.0f;
            float y = 720.0f + (i / 6) * 30.0f;
            gm->drawSprite(GRAFIC_FITXA_NEGRA, x, y);
        }

        //captura obligatoria?
        if (m_tauler.hiHaCapturaPossible(m_jugadorActual))
            gm->drawFont(FONT_GREEN_30, 400, 650, 0.8f, "CAPTURA OBLIGATORIA!"); 
    }
}

void Joc::dibuixaPantallaFinal()
{
    GraphicManager* gm = GraphicManager::getInstance();

    gm->drawFont(FONT_GREEN_30, 200, 650, 1.2f, "PARTIDA ACABADA!");

    string guanyador = "GUANYADOR: " + getStringColor(m_guanyador);

    FONT_NAME fontColor;
    if (m_guanyador == COLOR_BLANC)
        fontColor = FONT_WHITE_30;
    else
        fontColor = FONT_RED_30;


    gm->drawFont(fontColor, 200, 700, 1.0f, guanyador);
}

//auxiliars

//convertir coordenades del mouse a posició del tauler
Posicio Joc::converteixCoordenadesMouseATauler(int mousePosX, int mousePosY)
{
    int col = (mousePosX - POS_X_TAULER - CASELLA_INICIAL_X) / AMPLADA_CASELLA;
    int fila = N_FILES - 1 - ((mousePosY - POS_Y_TAULER - CASELLA_INICIAL_Y) / ALCADA_CASELLA);

    return Posicio(fila, col);
}

//comprobar si les coordenades estan dins del tauler
bool Joc::estaDinsLimitsTauler(int mousePosX, int mousePosY)
{
    int minX = POS_X_TAULER + CASELLA_INICIAL_X;
    int maxX = minX + N_COLUMNES * AMPLADA_CASELLA;
    int minY = POS_Y_TAULER + CASELLA_INICIAL_Y;
    int maxY = minY + N_FILES * ALCADA_CASELLA;

    return (mousePosX >= minX && mousePosX < maxX &&
        mousePosY >= minY && mousePosY < maxY);
}

//seleccionar una fitxa i calcular moviments possibles
void Joc::seleccionaFitxa(const Posicio& pos)
{
    m_fitxaSeleccionada = true;
    m_posicioSeleccionada = pos;
    m_posicionsValides.clear();

    // obtenir les posicions possibles
    Posicio posicionsPossibles[MAX_MOVIMENTS_POSSIBLES];
    int numPosicions = 0;

    m_tauler.getPosicionsPossibles(pos, numPosicions, posicionsPossibles);

    for (int i = 0; i < numPosicions; i++)//Es guarda al vector
        m_posicionsValides.push_back(posicionsPossibles[i]);
}

void Joc::executaMoviment(const Posicio& desti)
{
    //obtenir el moviment complet per saber les captures
    const Fitxa& fitxa = m_tauler.getFitxa(m_posicioSeleccionada);
    const vector<Moviment>& moviments = fitxa.getMoviments();
    Moviment movimentExecutat;

    for (const Moviment& mov : moviments)
    {
        if (mov.getPosicioFinal() == desti)
        {
            movimentExecutat = mov;
            break;
        }
    }

    //comproba si hi havia captures obligatòries ABANS de moure
    bool hiHaviaCapturesPossibles = m_tauler.hiHaCapturaPossible(m_jugadorActual);

    //actualitza el comptador de captures
    const vector<Posicio>& captures = movimentExecutat.getCaptures();
    for (const Posicio& captura : captures)
    {
        const Fitxa& fitxaCapturada = m_tauler.getFitxa(captura);
        if (fitxaCapturada.getColor() == COLOR_BLANC)
            m_fitxesBlanquesMortes++;
        else
            m_fitxesNegresMortes++;
    }

    if (m_tauler.mouFitxa(m_posicioSeleccionada, desti))
    {
        //guarda el moviment
        m_cua.afegeixMoviment(movimentExecutat);

        //aplica la regla de bufat si calia capturar i no s'ha fet la millor captura
        if (hiHaviaCapturesPossibles)
        {
            Moviment millorCaptura = m_tauler.obteMillorCaptura(m_jugadorActual);

            //si el moviment no es una captura o no es la millor captura
            if (movimentExecutat.getNumCaptures() == 0 ||
                (millorCaptura.esMovimentValid() &&
                    millorCaptura.getNumCaptures() > movimentExecutat.getNumCaptures()))
            {

                cout << "BUFAT! No has fet la captura obligatoria!" << endl;

                //elimianar la fitxa que acabem de moure
                m_tauler.eliminaFitxa(desti);

                //actualitzar el comptador
                if (m_jugadorActual == COLOR_BLANC)
                    m_fitxesBlanquesMortes++;
                else
                    m_fitxesNegresMortes++;

                //actualitza moviments després del bufat
                m_tauler.actualitzaMovimentsValids();
            }
        }

        //canvi de torn
        canviaTorn();

        //desseleccionar
        m_fitxaSeleccionada = false;
        m_posicionsValides.clear();
    }
}

bool Joc::esPosicioValida(const Posicio& pos)
{
    for (const Posicio& posValida : m_posicionsValides)
    {
        if (pos == posValida)
            return true;
    }
    return false;
}

void Joc::canviaTorn()
{
    if (m_jugadorActual == COLOR_BLANC)
        m_jugadorActual = COLOR_NEGRE;
    else
        m_jugadorActual = COLOR_BLANC;

    m_tauler.actualitzaMovimentsValids();
}

bool Joc::comprovaFinalPartida()
{
    int fitxesBlanques = 0, fitxesNegres = 0;
    bool potMoureBlanques = false, potMoureNegres = false;

    for (int fila = 0; fila < N_FILES; fila++)
    {
        for (int col = 0; col < N_COLUMNES; col++)
        {
            const Fitxa& fitxa = m_tauler.getFitxa(fila, col);
            if (fitxa.esFitxaJugador())
            {
                if (fitxa.getColor() == COLOR_BLANC)
                {
                    fitxesBlanques++;
                    if (!fitxa.getMoviments().empty())
                        potMoureBlanques = true;
                }
                else
                {
                    fitxesNegres++;
                    if (!fitxa.getMoviments().empty())
                        potMoureNegres = true;
                }
            }
        }
    }

    //partida acaba si un jugador no té fitxes o no pot moure
    return (fitxesBlanques == 0 || fitxesNegres == 0 ||
        (m_jugadorActual == COLOR_BLANC && !potMoureBlanques) ||
        (m_jugadorActual == COLOR_NEGRE && !potMoureNegres));
}

//obtenir el guanyador
ColorFitxa Joc::getGuanyador()
{
    int fitxesBlanques = 0, fitxesNegres = 0;

    for (int fila = 0; fila < N_FILES; fila++)
    {
        for (int col = 0; col < N_COLUMNES; col++)
        {
            const Fitxa& fitxa = m_tauler.getFitxa(fila, col);
            if (fitxa.esFitxaJugador())
            {
                if (fitxa.getColor() == COLOR_BLANC) fitxesBlanques++;
                else fitxesNegres++;
            }
        }
    }

    if (fitxesBlanques == 0) return COLOR_NEGRE;
    if (fitxesNegres == 0) return COLOR_BLANC;

    //si algú no pot moure, perd
    if (m_jugadorActual == COLOR_BLANC)
        return COLOR_NEGRE;
    else
        return COLOR_BLANC;
}

bool Joc::esFitxaDelJugadorActual(const Posicio& pos)
{
    const Fitxa& fitxa = m_tauler.getFitxa(pos);
    return fitxa.esFitxaJugador() && fitxa.getColor() == m_jugadorActual;
}

IMAGE_NAME Joc::obteImatgeFitxa(const Fitxa& fitxa)
{
    if (fitxa.getColor() == COLOR_BLANC)
    {
        if (fitxa.getTipus() == FITXA_NORMAL)
            return GRAFIC_FITXA_BLANCA;
        else
            return GRAFIC_DAMA_BLANCA;
    }
    else
    {
        if (fitxa.getTipus() == FITXA_NORMAL)
            return GRAFIC_FITXA_NEGRA;
        else
            return GRAFIC_DAMA_NEGRA;
    }
}

string Joc::getStringColor(ColorFitxa color)
{
    if (color == COLOR_BLANC)
        return "BLANQUES";
    else
        return "NEGRES";
}

string Joc::getStringModeJoc()
{
    switch (m_modeJoc)
    {
    case MODE_JOC_NORMAL: return "NORMAL";
    case MODE_JOC_REPLAY: return "REPLAY";
    default: return "DESCONEGUT";
    }
}