

#include "Jardineiro.h"

using namespace std;

bool Jardineiro::estaDentro() const { return dentro; }
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }


// Adiciona ao vetor
void Jardineiro::guardarFerramenta(Ferramenta* f) {
    // Define a posição como -1 (está no bolso, não no chão)
    f->setPosicao(-1, -1);
    inventario.push_back(f);
}

// Devolve a lista para podermos ler (lferr)
const vector<Ferramenta*>& Jardineiro::getInventario() const {
    return inventario;
}

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

// Tenta ativar uma ferramenta do inventário pelo ID
bool Jardineiro::pegarFerramenta(int id) {
    // 1. Procurar a ferramenta no inventário
    Ferramenta* encontrada = nullptr;
    for (Ferramenta* f : inventario) {
        if (f->getId() == id) {
            encontrada = f;
            break;
        }
    }
    // Se não encontrou, falha
    if (encontrada == nullptr) {
        return false;
    }

    // 2. Se já tínhamos uma na mão, largamo-la primeiro
    largarFerramenta();

    // 3. Pegar na nova
    ferramentaNaMao = encontrada;
    ferramentaNaMao->setAtiva(true); // Marca como ativa na classe Ferramenta

    return true;
}

// Desativa a ferramenta atual (guarda na mochila)
void Jardineiro::largarFerramenta() {
    if (ferramentaNaMao != nullptr) {
        ferramentaNaMao->setAtiva(false); // Deixa de estar ativa
        ferramentaNaMao = nullptr;        // A mão fica vazia
    }
}

