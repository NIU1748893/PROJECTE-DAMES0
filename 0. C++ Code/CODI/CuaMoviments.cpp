#include "CuaMoviments.h"
#include <fstream>
#include <sstream>

CuaMoviments::CuaMoviments() : m_inici(nullptr), m_fi(nullptr), m_mida(0) {}

CuaMoviments::~CuaMoviments() {
    while (!buida()) {
        Moviment m;
        treu(m);
    }
}

void CuaMoviments::afegeix(const Moviment& m) {
    Node* nouNode = new Node(m);
    if (m_fi == nullptr) {
        m_inici = m_fi = nouNode;
    }
    else {
        m_fi->seguent = nouNode;
        m_fi = nouNode;
    }
    m_mida++;
}

bool CuaMoviments::treu(Moviment& m) {
    if (buida()) {
        return false;
    }

    Node* temp = m_inici;
    m = temp->moviment;
    m_inici = m_inici->seguent;

    if (m_inici == nullptr) {
        m_fi = nullptr;
    }

    delete temp;
    m_mida--;
    return true;
}

bool CuaMoviments::buida() const {
    return m_inici == nullptr;
}

void CuaMoviments::guarda(const std::string& nomFitxer) const {
    std::ofstream fitxer(nomFitxer);
    if (!fitxer.is_open()) {
        return;
    }

    Node* actual = m_inici;
    while (actual != nullptr) {
        const std::vector<Posicio>& cami = actual->moviment.getCami();
        if (cami.size() >= 2) {
            fitxer << cami[0].toString() << " " << cami[1].toString() << "\n";
        }
        actual = actual->seguent;
    }
}

void CuaMoviments::carrega(const std::string& nomFitxer) {
    std::ifstream fitxer(nomFitxer);
    if (!fitxer.is_open()) {
        return;
    }

    while (!buida()) {
        Moviment m;
        treu(m);
    }

    std::string linia;
    while (getline(fitxer, linia)) {
        std::istringstream iss(linia);
        std::string pos1, pos2;
        iss >> pos1 >> pos2;

        Moviment m;
        m.afegeixPosicio(Posicio(pos1));
        m.afegeixPosicio(Posicio(pos2));
        afegeix(m);
    }
}

int CuaMoviments::getMida() const {
    return m_mida;
}