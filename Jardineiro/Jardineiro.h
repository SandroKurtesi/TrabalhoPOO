

#ifndef TP_JARDINEIRO_H
#define TP_JARDINEIRO_H

#include <iostream>
#include <vector>
#include "../Ferramentas/Ferramenta.h"

class Jardineiro {
    int linha = -1, coluna = -1;
    bool dentro = false;

    std::vector<Ferramenta*> inventario;
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

    void guardarFerramenta(Ferramenta* f);
    const std::vector<Ferramenta*>& getInventario() const;
};

#endif //TP_JARDINEIRO_H
