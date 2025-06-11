#pragma once
#ifndef CUAMOVIMENTS_H
#define CUAMOVIMENTS_H

#include "Moviment.h"
#include <string>
using namespace std;

class CuaMoviments
{
private:
    struct Node {
        Moviment moviment;
        Node* seguent;
        Node(const Moviment& m) : moviment(m), seguent(nullptr) {}
    };

    Node* m_inici;
    Node* m_fi;
    int m_mida;

public:
    CuaMoviments();
    ~CuaMoviments();
    void afegeix(const Moviment& m);
    bool treu(Moviment& m);
    bool buida() const;
    void guarda(const string& nomFitxer) const;
    void carrega(const string& nomFitxer);
    int getMida() const;
};

#endif