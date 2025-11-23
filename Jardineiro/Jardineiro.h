

#ifndef TP_JARDINEIRO_H
#define TP_JARDINEIRO_H

#include <iostream>

class Jardineiro {
    int linha = -1, coluna = -1;
    bool dentro = false;

public:
    Jardineiro() = default; // indica ao compilador para disponibilizar o construtor por omissão

    bool estaDentro() const;
    int getLinha() const;
    int getColuna() const;

    void entra(int l, int c, int maxLinhas, int maxColunas);
    void sai();

    void moverCima();
    void moverBaixo(int maxLinhas);
    void moverEsquerda();
    void moverDireita(int maxColunas);

    char getRepresentacao() const { return '*'; }
};

#endif //TP_JARDINEIRO_H
