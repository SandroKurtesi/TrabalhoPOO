#include "Jardim.h"
#include <iostream>

// Tens de incluir os .h das plantas especificas para as conseguires criar
#include "../Plantas/tipos/PlantaExotica/PlantaExotica.h"
#include "../Plantas/tipos/ErvaDaninha/ErvaDaninha.h"
#include "../Plantas/tipos/Cacto/Cacto.h"
#include "../Plantas/tipos/Roseira/Roseira.h"

using namespace std;

// Construtor
Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i)
        grelha[i] = new Solo[colunas];
}

// Destrutor (Atualizado para limpar as plantas também)
Jardim::~Jardim() {
    // 1. Limpar a grelha
    for (int i = 0; i < linhas; ++i)
        delete[] grelha[i];
    delete[] grelha;

    // 2. Limpar as plantas da memória
    for (Planta* p : plantas) {
        delete p;
    }
    plantas.clear();
}

// Getters
Jardineiro &Jardim::getJardineiro() { return jardineiro; }
int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }
bool Jardim::dimensoesValidas(int l, int c) { return l > 0 && l <= 26 && c > 0 && c <= 26; }


// --- FUNÇÃO NOVA: Adicionar Planta ---
bool Jardim::adicionarPlanta(const std::string& tipo, int l, int c) {
    // 1. Validar Limites
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        return false;
    }

    // 2. Verificar se já existe uma planta nessa posição
    for (Planta* p : plantas) {
        if (p->getLinha() == l && p->getColuna() == c) {
            return false; // Posição ocupada
        }
    }

    // 3. Criar a planta correta (Factory)
    Planta* nova = nullptr;

    // Verifica a primeira letra ou o nome completo (para ser flexível)
    // Nota: assume que 'tipo' vem em minúsculas do Simulador
    if (tipo == "roseira" || tipo == "r") {
        nova = new Roseira(l, c);
    }
    else if (tipo == "cacto" || tipo == "c") {
        nova = new Cacto(l, c);
    }
    else if (tipo == "erva" || tipo == "e") {
        nova = new ErvaDaninha(l, c);
    }
    else if (tipo == "exotica" || tipo == "x") {
        nova = new PlantaExotica(l, c);
    }

    // 4. Guardar na lista se foi criada com sucesso
    if (nova != nullptr) {
        plantas.push_back(nova);
        return true;
    }

    return false; // Tipo desconhecido
}


// --- FUNÇÃO ATUALIZADA: Mostrar ---
void Jardim::mostrar() const {
    // Régua de cima
    cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        cout << char('A' + j);
    }
    cout << "\n";

    for (int i = 0; i < linhas; ++i) {
        // Régua lateral
        cout << char('A' + i) << " ";

        for (int j = 0; j < colunas; ++j) {

            // 1. PRIORIDADE MÁXIMA: Jardineiro
            if (jardineiro.estaDentro() && i == jardineiro.getLinha() && j == jardineiro.getColuna()) {
                cout << jardineiro.getRepresentacao();
            }
            else {
                // 2. PRIORIDADE MÉDIA: Plantas
                bool desenhouPlanta = false;

                // Procura na lista se há alguma planta nesta posição (i, j)
                for (Planta* p : plantas) {
                    if (p->getLinha() == i && p->getColuna() == j) {
                        cout << p->getRepresentacao(); // Desenha 'r', 'c', etc.
                        desenhouPlanta = true;
                        break; // Encontrou, pára de procurar e avança
                    }
                }

                // 3. PRIORIDADE MÍNIMA: Solo
                // Só desenha o solo se não desenhou planta nem jardineiro
                if (!desenhouPlanta) {
                    cout << grelha[i][j].getRepresentacao();
                }
            }
        }
        cout << "\n";
    }
}