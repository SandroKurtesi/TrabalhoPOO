#include "Jardim.h"
#include <iostream>


#include "../Plantas/tipos/PlantaExotica/PlantaExotica.h"
#include "../Plantas/tipos/ErvaDaninha/ErvaDaninha.h"
#include "../Plantas/tipos/Cacto/Cacto.h"
#include "../Plantas/tipos/Roseira/Roseira.h"
#include "../Ferramentas/tipos/Adubo/Adubo.h"
#include "../Ferramentas/tipos/Tesoura/Tesoura.h"
#include "../Ferramentas/tipos/Regador/Regador.h"
#include "../Ferramentas/tipos/FerramentaZ/FerramentaZ.h"
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

    for (Ferramenta* f : ferramentas) {
        delete f;
    }
    ferramentas.clear();
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


bool Jardim::adicionarFerramenta(const std::string& tipo, int l, int c) {
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) return false;

    // Criar a ferramenta certa
    Ferramenta* nova = nullptr;

    if (tipo == "regador" || tipo == "g") {
        nova = new Regador(l, c);
    }
    else if (tipo == "adubo" || tipo == "a") {
        nova = new Adubo(l, c);
    }
    else if (tipo == "tesoura" || tipo == "t") {
        nova = new Tesoura(l, c);
    }
    else if (tipo == "z") {
        nova = new FerramentaZ(l, c);
    }

    if (nova != nullptr) {
        ferramentas.push_back(nova);
        return true;
    }
    return false;
}



void Jardim::mostrar() const {
    // 1. Imprimir a "Régua" de cima (A B C D ...)
    cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        cout << char('A' + j); // Imprime as letras das colunas
    }
    cout << "\n";

    // 2. Percorrer todas as linhas
    for (int i = 0; i < linhas; ++i) {

        // Imprimir a "Régua" lateral (A B C D ...)
        cout << char('A' + i) << " ";

        // Percorrer todas as colunas desta linha
        for (int j = 0; j < colunas; ++j) {

            bool desenhou = false; // Flag para saber se já desenhámos algo nesta casa

            // --- PRIORIDADE 1: O JARDINEIRO ---
            // Verifica se o jardineiro está no jardim e se está nesta posição (i, j)
            if (jardineiro.estaDentro() && i == jardineiro.getLinha() && j == jardineiro.getColuna()) {
                cout << jardineiro.getRepresentacao(); // Desenha '*'
                desenhou = true;
            }

            // --- PRIORIDADE 2: AS PLANTAS ---
            // Só verifica plantas se ainda não desenhou o jardineiro
            if (!desenhou) {
                for (Planta* p : plantas) {
                    if (p->getLinha() == i && p->getColuna() == j) {
                        cout << p->getRepresentacao(); // Desenha 'r', 'c', etc.
                        desenhou = true;
                        break; // Já encontrou uma planta, pára de procurar e sai do loop das plantas
                    }
                }
            }

            // --- PRIORIDADE 3: AS FERRAMENTAS ---
            // Só verifica ferramentas se não desenhou jardineiro nem planta
            if (!desenhou) {
                for (Ferramenta* f : ferramentas) {
                    if (f->getLinha() == i && f->getColuna() == j) {
                        cout << f->getRepresentacao(); // Desenha 'g', 'a', 't', 'z'
                        desenhou = true;
                        break; // Já encontrou uma ferramenta, pára de procurar
                    }
                }
            }

            // --- PRIORIDADE 4: O SOLO ---
            // Se não havia nada, desenha o solo (que é " " ou outro caracter)
            if (!desenhou) {
                cout << grelha[i][j].getRepresentacao();
            }
        }
        // Fim da linha, muda para a próxima
        cout << "\n";
    }
}
void Jardim::infoSolo(int l, int c) const {
    // 1. Validar
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        cout << "Coordenadas invalidas.\n";
        return;
    }

    // 2. Mostrar Dados do Solo
    // (Nota: estou a assumir que tens getAgua() e getNutrientes() na classe Solo)
    Solo& s = grelha[l][c];
    cout << "--- INFO SOLO (" << char('A' + l) << char('A' + c) << ") ---\n";
    cout << "Agua: " << s.getAgua() << " | Nutrientes: " << s.getNutrientes() << "\n";

    // 3. O que esta aqui?
    cout << "Ocupantes:\n";

    // a) Jardineiro?
    if (jardineiro.estaDentro() && jardineiro.getLinha() == l && jardineiro.getColuna() == c) {
        cout << " - [JARDINEIRO]\n";
    }

    // b) Planta?
    for (Planta* p : plantas) {
        if (p->getLinha() == l && p->getColuna() == c) {
            cout << " - [PLANTA] " << p->getTipo() << " (" << p->getRepresentacao() << ")\n";
            // Futuramente podes mostrar mais detalhes da planta aqui
        }
    }

    // c) Ferramentas?
    for (Ferramenta* f : ferramentas) {
        if (f->getLinha() == l && f->getColuna() == c) {
            cout << " - [FERRAMENTA] " << f->getTipo() << " (ID: " << f->getId() << ")\n";
        }
    }
}

bool Jardim::colherPlanta(int l, int c) {

    if (l < 0 || l >= linhas || c < 0 || c >= colunas) return false;

    // 2. Validar Regras do Jardineiro (Limite de 5)
    if (!jardineiro.podeColher()) {
        cout << "O jardineiro esta cansado! (Max 5 colheitas por turno)\n";
        return false;
    }

    // 3. Procurar a planta na lista
    for (auto it = plantas.begin(); it != plantas.end(); ++it) {
        Planta* p = *it;

        if (p->getLinha() == l && p->getColuna() == c) {
            // ENCONTROU!

            // a) Apagar o objeto da memória (ESSENCIAL!)
            delete p;

            // b) Remover o ponteiro da lista
            plantas.erase(it);

            // c) Atualizar o contador do jardineiro
            jardineiro.registarColheita();

            return true; // Sucesso
        }
    }

    cout << "Nao ha planta nessa posicao.\n";
    return false;
}

void Jardim::avancaInstante() {
    // 1. O Jardineiro descansa (Reset aos contadores de ações)
    // Isto permite que ele volte a colher mais 5 plantas no próximo turno
    jardineiro.resetTurno();

    // 2. Atualizar as Plantas (Envelhecer, beber, morrer)
    // Usamos um iterador para podermos remover plantas da lista enquanto percorremos
    auto it = plantas.begin();
    while (it != plantas.end()) {
        Planta* p = *it;

        // Descobre o solo onde a planta está
        Solo& soloDaPlanta = grelha[p->getLinha()][p->getColuna()];

        // Manda a planta viver o seu turno
        p->atualizar(soloDaPlanta);

        // Verifica se morreu
        if (!p->estaViva()) {
            cout << "A planta " << p->getRepresentacao()
                 << " (" << p->getTipo() << ") morreu na posicao "
                 << char('A' + p->getLinha()) << char('A' + p->getColuna()) << ".\n";

            // Limpa a memória
            delete p;
            // Remove da lista e atualiza o iterador para o próximo
            it = plantas.erase(it);
        } else {
            // Se está viva, avança para a próxima
            ++it;
        }
    }
}

// 1. IMPLEMENTAÇÃO DE lplantas
void Jardim::listarTodasPlantas() const {
    cout << "=== LISTA DE PLANTAS DO JARDIM ===\n";
    if (plantas.empty()) {
        cout << "(Nenhuma planta no jardim)\n";
        return;
    }

    for (const Planta* p : plantas) {
        // Chama o getDescricao() que criaste no Passo 1
        cout << " - " << p->getDescricao() << "\n";

        // Mostra também o solo onde ela está (requisito do enunciado)
        const Solo& s = grelha[p->getLinha()][p->getColuna()];
        cout << "   [Solo] Agua: " << s.getAgua() << " Nutr: " << s.getNutrientes() << "\n";
    }
}

// 2. IMPLEMENTAÇÃO DE lplanta <l><c>
void Jardim::listarPlanta(int l, int c) const {
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        cout << "Coordenadas invalidas.\n";
        return;
    }

    bool encontrou = false;
    for (const Planta* p : plantas) {
        if (p->getLinha() == l && p->getColuna() == c) {
            cout << "--- DETALHE DA PLANTA ---\n";
            cout << p->getDescricao() << "\n";
            encontrou = true;
            // Não fazemos break porque teoricamente (no futuro)
            // podiam haver duas coisas, embora as regras agora não deixem.
        }
    }

    if (!encontrou) {
        cout << "Nao existe nenhuma planta na posicao "
             << (char)('A' + l) << (char)('A' + c) << ".\n";
    }
}

// 3. IMPLEMENTAÇÃO DE larea
// Lista tudo o que NÃO é vazio
void Jardim::listarArea() const {
    cout << "=== LISTAGEM DA AREA NAO-VAZIA ===\n";

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            bool temAlgo = false;

            // Verifica se tem Jardineiro
            if (jardineiro.estaDentro() && jardineiro.getLinha() == i && jardineiro.getColuna() == j)
                temAlgo = true;

            // Verifica se tem Planta
            if (!temAlgo) {
                for (auto p : plantas)
                    if (p->getLinha() == i && p->getColuna() == j) { temAlgo = true; break; }
            }

            // Verifica se tem Ferramenta
            if (!temAlgo) {
                for (auto f : ferramentas)
                    if (f->getLinha() == i && f->getColuna() == j) { temAlgo = true; break; }
            }

            // Se tiver alguma coisa, reutilizamos o infoSolo() que já tinhas feito!
            if (temAlgo) {
                infoSolo(i, j); // <--- Reutilização inteligente de código
                cout << "-----------------------------\n";
            }
        }
    }
}