

#include "Jardineiro.h"

using namespace std;

bool Jardineiro::estaDentro() const { return dentro; }
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }

void Jardineiro::entra(int l, int c, int maxLinhas, int maxColunas) {
    if (l < 0 || l >= maxLinhas || c < 0 || c >= maxColunas) {
        cout << "Posicao fora dos limites do jardim.\n";
        return;
    }

    linha = l;
    coluna = c;
    dentro = true;
}

void Jardineiro::sai() {
    if (!dentro) {
        cout << "O jardineiro já está fora do jardim.\n";
        return;
    }
    dentro = false;
    cout << "O jardineiro saiu do jardim.\n";
}

void Jardineiro::moverCima() {
    if (!dentro) return;
    if (linha > 0) linha--;
}

void Jardineiro::moverBaixo(int maxLinhas) {
    if (!dentro) return;
    if (linha < maxLinhas - 1) linha++;
}

void Jardineiro::moverEsquerda() {
    if (!dentro) return;
    if (coluna > 0) coluna--;
}

void Jardineiro::moverDireita(int maxColunas) {
    if (!dentro) return;
    if (coluna < maxColunas - 1) coluna++;
}

