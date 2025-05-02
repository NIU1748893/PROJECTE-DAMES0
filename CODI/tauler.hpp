#include "Tauler.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Tauler::inicialitza(const string& nomFitxer)
{
    // Inicialitzar tot buit
    for (int i = 0; i < N_FILES; ++i)
    {
        for (int j = 0; j < N_COLUMNES; ++j)
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC);

    }
    ifstream fitxer(nomFitxer);
    string linia;

    while (getline(fitxer, linia))
    {
        istringstream iss(linia);
        char tipusChar;
        string pos;
        iss >> tipusChar >> pos;

        TipusFitxa tipus;
        ColorFitxa color;

        switch (tipusChar)
        {
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

void Tauler::actualitzaMovimentsValids()
{
    for (int fila = 0; fila < N_FILES; fila++) 
    {
        for (int col = 0; col < N_COLUMNES; col++) 
        {
            if (!m_tauler[fila][col].esBuida())
                m_tauler[fila][col].netejaMoviments();
        }
    }
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    int fila = origen.getFila();
    int col = origen.getColumna();

    if (fila < 0 || fila >= N_FILES || col < 0 || col >= N_COLUMNES || m_tauler[fila][col].esBuida())
        return;

    Fitxa fitxa = m_tauler[fila][col];
    TipusFitxa tipus = fitxa.getTipus();
    ColorFitxa color = fitxa.getColor();

    if (tipus == TIPUS_NORMAL) {
        int direccion = (color == COLOR_BLANC) ? -1 : 1;

        for (int dc = -1; dc <= 1; dc += 2)
        {
            int nuevaFila = fila + direccion;
            int nuevaCol = col + dc;
            if (nuevaFila >= 0 && nuevaFila < N_FILES && nuevaCol >= 0 && nuevaCol < N_COLUMNES)
            {
                if (m_tauler[nuevaFila][nuevaCol].esBuida())
                    posicionsPossibles[nPosicions++] = Posicio(nuevaFila, nuevaCol);
            }
        }

        for (int dc = -2; dc <= 2; dc += 4)
        {
            int nuevaFila = fila + 2 * direccion;
            int nuevaCol = col + dc;
            int filaIntermedia = fila + direccion;
            int colIntermedia = col + dc / 2;

            if (nuevaFila >= 0 && nuevaFila < N_FILES && nuevaCol >= 0 && nuevaCol < N_COLUMNES)
            {
                if (m_tauler[nuevaFila][nuevaCol].esBuida() && !m_tauler[filaIntermedia][colIntermedia].esBuida() && m_tauler[filaIntermedia][colIntermedia].getColor() != color)
                    posicionsPossibles[nPosicions++] = Posicio(nuevaFila, nuevaCol);
            }
        }
    }
    else if (tipus == TIPUS_DAMA)
    {
        for (int df = -1; df <= 1; df += 2)
        {
            for (int dc = -1; dc <= 1; dc += 2)
            {
                for (int pasos = 1; pasos < N_FILES; pasos++)
                {
                    int nuevaFila = fila + df * pasos;
                    int nuevaCol = col + dc * pasos;

                    if (nuevaFila < 0 || nuevaFila >= N_FILES || nuevaCol < 0 || nuevaCol >= N_COLUMNES)
                        break;

                    if (m_tauler[nuevaFila][nuevaCol].esBuida())
                        posicionsPossibles[nPosicions++] = Posicio(nuevaFila, nuevaCol); 
                    else
                    {
                        if (m_tauler[nuevaFila][nuevaCol].getColor() != color)
                        {
                            int filaCaptura = nuevaFila + df;
                            int colCaptura = nuevaCol + dc;

                            if (filaCaptura >= 0 && filaCaptura < N_FILES && colCaptura >= 0 && colCaptura < N_COLUMNES && m_tauler[filaCaptura][colCaptura].esBuida())
                                posicionsPossibles[nPosicions++] = Posicio(filaCaptura, colCaptura);
                        }
                        break;
                    }
                }
            }
        }
    }
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    int filaOrigen = origen.getFila();
    int colOrigen = origen.getColumna();
    int filaDesti = desti.getFila();
    int colDesti = desti.getColumna();

    if (filaOrigen < 0 || filaOrigen >= N_FILES || colOrigen < 0 || colOrigen >= N_COLUMNES ||
        filaDesti < 0 || filaDesti >= N_FILES || colDesti < 0 || colDesti >= N_COLUMNES ||
        m_tauler[filaOrigen][colOrigen].esBuida() || !m_tauler[filaDesti][colDesti].esBuida())
        return false;

    int nPosicions;
    Posicio posicionsPossibles[8];
    getPosicionsPossibles(origen, nPosicions, posicionsPossibles);

    bool movimentValid = false;
    for (int i = 0; i < nPosicions; i++)
    {
        if (posicionsPossibles[i] == desti)
        {
            movimentValid = true;
            break;
        }
    }
    if (!movimentValid)
        return false;

    m_tauler[filaDesti][colDesti] = m_tauler[filaOrigen][colOrigen];
    m_tauler[filaOrigen][colOrigen] = Fitxa();

    int df = abs(filaDesti - filaOrigen);
    int dc = abs(colDesti - colOrigen);

    if (df >= 2 || dc >= 2)
    {
        int pasoFila = (filaDesti > filaOrigen) ? 1 : -1;
        int pasoCol = (colDesti > colOrigen) ? 1 : -1;

        int f = filaOrigen + pasoFila;
        int c = colOrigen + pasoCol;
        while (f != filaDesti && c != colDesti)
        {
            if (!m_tauler[f][c].esBuida())
                m_tauler[f][c] = Fitxa();
            f += pasoFila;
            c += pasoCol;
        }
    }
    if (m_tauler[filaDesti][colDesti].getTipus() == TIPUS_NORMAL)
    {
        bool esBlancaEnUltimaFila = (m_tauler[filaDesti][colDesti].getColor() == COLOR_BLANC && filaDesti == 0);
        bool esNegraEnPrimeraFila = (m_tauler[filaDesti][colDesti].getColor() == COLOR_NEGRE && filaDesti == N_FILES - 1);

        if (esBlancaEnUltimaFila || esNegraEnPrimeraFila)
            m_tauler[filaDesti][colDesti].convertirADama();
    }

    return true;
}

string Tauler::toString() const
{
    stringstream ss;
    for (int fila = 0; fila < N_FILES; fila++)
    {
        ss << (N_FILES - fila) << ": ";
        for (int col = 0; col < N_COLUMNES; col++)
        {
            if (m_tauler[fila][col].esBuida())
                ss << '_';
            else
            {
                TipusFitxa tipus = m_tauler[fila][col].getTipus();
                ColorFitxa color = m_tauler[fila][col].getColor();

                if (tipus == TIPUS_NORMAL)
                {
                    if (color == COLOR_BLANC)
                        ss << 'O';
                    else
                        ss << 'X';
                }
                else
                {
                    if (color == COLOR_BLANC)
                        ss << 'D';
                    else
                        ss << 'R';
                }
            }
            if (col != N_COLUMNES - 1) ss << ' ';
        }
        ss << '\n';
    }
    ss << "   a b c d e f g h";
    return ss.str();
}
