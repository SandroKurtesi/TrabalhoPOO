

#include "Jardineiro.h"

using namespace std;

bool Jardineiro::estaDentro() const { return dentro; }
int Jardineiro::getLinha() const { return linha; }
int Jardineiro::getColuna() const { return coluna; }




void Jardineiro::resetTurno() {
    movimentosTurno = 0;
    colheitasNesteTurno = 0;
    plantacoesTurno = 0;
    entradasTurno = 0;
    saidasTurno = 0;
}
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

    if (!podeEntrar()) { std::cout << "Ja entrou neste turno!\n"; return; }
    if (l < 0 || l >= maxLinhas || c < 0 || c >= maxColunas) {
        cout << "Posicao fora dos limites do jardim.\n";
        return;
    }

    linha = l;
    coluna = c;
    dentro = true;
    registarEntrada();
}

void Jardineiro::sai() {
    if (!dentro) return;
    if (!podeSair()) { std::cout << "Ja saiu neste turno!\n"; return; }
    dentro = false;
    registarSaida();
}

void Jardineiro::moverCima() {
    if (!dentro) return;
    if (!podeMover()) { std::cout << "Cansado! (Max 10 movimentos)\n"; return; }

    if (linha > 0) {
        linha--;
        registarMovimento(); }
}

void Jardineiro::moverBaixo(int maxLinhas) {
    if (!dentro) return;
    if (!podeMover()) {
        std::cout << "Cansado! (Max 10 movimentos)\n";
        return;
    }

    if (linha < maxLinhas - 1) {
        linha++;
        registarMovimento();
    };
}

void Jardineiro::moverEsquerda() {
    if (!dentro) return;
    if (!podeMover()) {
        std::cout << "Cansado! (Max 10 movimentos)\n";
        return;
    }

    if (coluna > 0) {
        coluna--;
        registarMovimento();
    }
}

void Jardineiro::moverDireita(int maxColunas) {
    if (!dentro) return;
    if (!podeMover()) {
        std::cout << "Cansado! (Max 10 movimentos)\n";
        return;
    }

    if (coluna < maxColunas - 1){
        coluna++;
        registarMovimento();
    }
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

void Jardineiro::removerFerramentaDaMao() {
    if (ferramentaNaMao == nullptr) return;

    // Procura a ferramenta no inventário e remove-a do vetor
    for (auto it = inventario.begin(); it != inventario.end(); ++it) {
        if (*it == ferramentaNaMao) {
            inventario.erase(it);
            break;
        }
    }
    // Esvazia a mão (mas NÃO faz delete, isso é feito por quem chama esta função)
    ferramentaNaMao = nullptr;
}

bool Jardineiro::podeMover() const { return movimentosTurno < Settings::Jardineiro::max_movimentos; }
void Jardineiro::registarMovimento() { movimentosTurno++; }

// --- COLHEITA (MAX 5) ---
bool Jardineiro::podeColher() const { return colheitasNesteTurno < Settings::Jardineiro::max_colheitas; }
void Jardineiro::registarColheita() { colheitasNesteTurno++; }

// --- PLANTAR (MAX 2) ---
bool Jardineiro::podePlantar() const { return plantacoesTurno < Settings::Jardineiro::max_plantacoes; }
void Jardineiro::registarPlantacao() { plantacoesTurno++; }

// --- ENTRAR (MAX 1) ---
bool Jardineiro::podeEntrar() const { return entradasTurno < Settings::Jardineiro::max_entradas_saidas; }
void Jardineiro::registarEntrada() { entradasTurno++; }

// --- SAIR (MAX 1) ---
bool Jardineiro::podeSair() const { return saidasTurno < Settings::Jardineiro::max_entradas_saidas; }
void Jardineiro::registarSaida() { saidasTurno++; }

