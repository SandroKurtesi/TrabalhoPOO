

#include "Jardim.h"

using namespace std;

Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i)
        grelha[i] = new Solo[colunas];
}

Jardim::~Jardim() {
    for (int i = 0; i < linhas; ++i)
        delete[] grelha[i];
    delete[] grelha;
}

void Jardim::mostrar() const {
    cout << " ";
    // cout << "  ";  depois quero usar este pra muita estetica

    for (int j = 0; j < colunas; ++j) {
        cout << char('A' + j);
      //  cout << "  "; este tb é pra estetica
    }
    cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        cout << char('A' + i) << " ";
        for (int j = 0; j < colunas; ++j) {
            if (jardineiro.estaDentro() && i == jardineiro.getLinha() && j == jardineiro.getColuna())
                cout << jardineiro.getRepresentacao();
            else
                cout << grelha[i][j].getRepresentacao();
        }
        cout << "\n";
    }
}

bool Jardim::dimensoesValidas(int l, int c) {
    return l > 0 && l <= 26 && c > 0 && c <= 26;
}

Jardineiro &Jardim::getJardineiro() {
    return jardineiro;
}

int Jardim::getLinhas() const { return linhas; }

int Jardim::getColunas() const { return colunas; }


