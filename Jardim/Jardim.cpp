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
#include "../Plantas/tipos/PlantaExotica/PlantaExotica.h"
using namespace std;

// Construtor
Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i)
        grelha[i] = new Solo[colunas];
    for (int i = 0; i < 3; i++) {
        spawnFerramentaAleatoria();
    }
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


void Jardim::spawnFerramentaAleatoria() {
    // Proteção: Se o jardim estiver cheio de ferramentas, não cria mais (evita loop infinito)
    if (ferramentas.size() >= linhas * colunas) return;

    int l, c;
    bool ocupada;

    // Loop: Gera coordenadas até encontrar uma posição SEM ferramentas
    do {
        l = rand() % linhas;
        c = rand() % colunas;
        ocupada = false;

        // Verifica se já existe alguma ferramenta nesta posição (l, c)
        for (Ferramenta* f : ferramentas) {
            if (f->getLinha() == l && f->getColuna() == c) {
                ocupada = true;
                break;
            }
        }
    } while (ocupada);

    // Agora que temos (l,c) livres, criamos a ferramenta
    int tipo = rand() % 4; // 0, 1, 2, 3
    Ferramenta* nova = nullptr;

    if (tipo == 0) nova = new Regador(l, c);
    else if (tipo == 1) nova = new Adubo(l, c);
    else if (tipo == 2) nova = new Tesoura(l, c);
    else nova = new FerramentaZ(l, c);

    if (nova != nullptr) {
        ferramentas.push_back(nova);
    }
}

void Jardim::verificarFerramentasNoChao() {
    if (!jardineiro.estaDentro()) return;

    auto it = ferramentas.begin();
    while (it != ferramentas.end()) {
        Ferramenta* f = *it;

        // Se o jardineiro estiver na mesma posicao da ferramenta
        if (f->getLinha() == jardineiro.getLinha() && f->getColuna() == jardineiro.getColuna()) {

            cout << "Encontraste uma ferramenta: " << f->getTipo() << " (ID: " << f->getId() << ")!\n";

            // 1. O Jardineiro guarda-a
            jardineiro.guardarFerramenta(f);

            // 2. Removemos do chão (lista do jardim)
            it = ferramentas.erase(it);

            // 3. Regra Magica: Aparece outra noutro sitio!
            spawnFerramentaAleatoria();

        } else {
            ++it;
        }
    }
}


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

// Função auxiliar para aceder ao Solo de forma segura
Solo& Jardim::getSolo(int l, int c) const {
    // Se as coordenadas forem inválidas, devolve o solo da posição 0,0
    // (apenas para evitar que o programa vá abaixo)
    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        return grelha[0][0];
    }
    // Retorna o solo na posição pedida
    return grelha[l][c];
}


void Jardim::avancaInstante() {
    // 1. O Jardineiro descansa (Reset aos contadores)
    jardineiro.resetTurno();



    // Lista temporária para guardar os bebés que nascerem neste turno
    vector<Planta*> novasPlantas;


    if (jardineiro.estaDentro()) {
        Ferramenta* f = jardineiro.getFerramentaNaMao();

        if (f != nullptr) {
            // Verifica se é uma Tesoura (pelo tipo ou cast)
            if (f->getTipo() == "Tesoura") { // Ou verifica o ID se preferires
                removerPlanta(jardineiro.getLinha(), jardineiro.getColuna());
            }
            else {
                // Se for Adubo ou Regador, usa normalmente no solo
                f->usar(grelha[jardineiro.getLinha()][jardineiro.getColuna()]);
            }
        }
    }
    // 3. CICLO DE VIDA DAS PLANTAS
    auto it = plantas.begin();
    while (it != plantas.end()) {
        Planta* mae = *it;

        // Obtém o solo onde a planta está
        Solo& soloMae = grelha[mae->getLinha()][mae->getColuna()];

        // A. Atualizar (Beber, Comer, Envelhecer)
        mae->atualizar(soloMae);

        // B. Verificar Morte
        if (!mae->estaViva()) {
            cout << "Planta " << mae->getRepresentacao() << " morreu na posicao "
                 << (char)('A' + mae->getLinha()) << (char)('A' + mae->getColuna()) << ".\n";

            delete mae;             // Limpa memória
            it = plantas.erase(it); // Remove da lista e atualiza o iterador
            continue;               // Passa logo para a próxima
        }

        // C. Verificar Reprodução
        if (mae->podemMultiplicar(soloMae)) {

            // --- CORREÇÃO: Declarar as variáveis ANTES de usar ---
            int filhoL = -1;
            int filhoC = -1;

            // Agora passamos as variáveis para serem preenchidas
            if (getVizinhaLivre(mae->getLinha(), mae->getColuna(), filhoL, filhoC)) {

                Planta* bebe = nullptr;
                string tipo = mae->getTipo();

                // --- CRIAÇÃO DOS BEBÉS E REGRAS DE PARTILHA ---

                if (tipo == "Roseira") {
                    bebe = new Roseira(filhoL, filhoC);
                    // Regra Roseira: "Original fica com 100 nutr e metade da agua"
                    // "Bebé começa com 25 nutr e metade da agua da mãe"
                    int aguaTotal = mae->getAgua();

                    mae->setNutrientes(100);
                    mae->setAgua(aguaTotal / 2);

                    bebe->setNutrientes(25);
                    bebe->setAgua(aguaTotal / 2);
                }
                else if (tipo == "Cacto") {
                    bebe = new Cacto(filhoL, filhoC);
                    // Regra Cacto: "Agua e nutrientes divididos em iguais partes"
                    int aguaMae = mae->getAgua();
                    int nutrMae = mae->getNutrientes();

                    mae->setAgua(aguaMae / 2);
                    mae->setNutrientes(nutrMae / 2);

                    bebe->setAgua(aguaMae / 2);
                    bebe->setNutrientes(nutrMae / 2);
                }
                else if (tipo == "ErvaDaninha") {
                    bebe = new ErvaDaninha(filhoL, filhoC);
                    // Regra Erva: "Nova fica com 5/5, a inicial não perde nada"
                    // (O construtor já mete 5/5, não precisamos de fazer nada)
                }
                else if (tipo == "PlantaExotica") {
                    bebe = new PlantaExotica(filhoL, filhoC);

                    // Regra: O filho nasce com metade dos nutrientes da mãe
                    int metadeNutr = mae->getNutrientes() / 2;

                    bebe->setNutrientes(metadeNutr);
                    mae->setNutrientes(metadeNutr); // A mãe perde metade

                    // Água mantém-se igual (ela não gasta muita água)
                    bebe->setAgua(mae->getAgua());
                }

                // Se o bebé foi criado, adiciona à lista temporária
                // ... (dentro do if (bebe != nullptr)) ...
                if (bebe != nullptr) {
                    novasPlantas.push_back(bebe);
                    cout << "Nova " << tipo << " nasceu em "
                         << (char)('A' + filhoL) << (char)('A' + filhoC) << "!\n";

                    // --- CORREÇÃO AQUI: AVISAR A MÃE ---
                    mae->posReproducao();
                }
            }
        }

        ++it; // Avança para a próxima planta mãe
    }

    // 4. Adicionar os bebés à lista oficial do Jardim
    for (Planta* p : novasPlantas) {
        plantas.push_back(p);
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

// Helper para encontrar uma posição livre à volta de (l, c)
// Retorna true se encontrou e preenche as variaveis 'resL' e 'resC'
bool Jardim::getVizinhaLivre(int l, int c, int& resL, int& resC) {
    // Vetores de deslocamento (Cima, Baixo, Esquerda, Direita)
    int dL[] = {-1, 1, 0, 0};
    int dC[] = {0, 0, -1, 1};

    // Começar num índice aleatório para as plantas não crescerem sempre para Cima
    int start = rand() % 4;

    for (int i = 0; i < 4; i++) {
        int idx = (start + i) % 4; // Garante que damos a volta ao array (0,1,2,3)

        int vizL = l + dL[idx];
        int vizC = c + dC[idx];

        // 1. Validar Limites do Jardim
        if (vizL >= 0 && vizL < linhas && vizC >= 0 && vizC < colunas) {

            // 2. Verificar se está ocupado por outra planta
            bool ocupado = false;
            for (Planta* p : plantas) {
                if (p->getLinha() == vizL && p->getColuna() == vizC) {
                    ocupado = true;
                    break;
                }
            }

            // Se não estiver ocupado, encontrámos!
            if (!ocupado) {
                resL = vizL;
                resC = vizC;
                return true;
            }
        }
    }
    return false; // Não há espaço à volta
}

void Jardim::removerPlanta(int l, int c) {
    auto it = plantas.begin();
    while (it != plantas.end()) {
        Planta* p = *it;
        if (p->getLinha() == l && p->getColuna() == c) {
            cout << "A Tesoura cortou a planta " << p->getTipo() << " em " << l << "," << c << "!\n";
            delete p;            // Liberta a memória
            it = plantas.erase(it); // Remove do vetor
            return; // Já cortou, pode sair
        } else {
            ++it;
        }
    }
    cout << "Nenhuma planta para cortar aqui.\n";
}

#include <fstream> // Precisas disto no topo

bool Jardim::salvarEstado(const string& nomeFicheiro) const {
    ofstream f(nomeFicheiro); // Abre ficheiro para escrita
    if (!f.is_open()) return false;

    // 1. DADOS GERAIS
    f << "JARDIM " << linhas << " " << colunas << "\n";

    // 2. JARDINEIRO (Posição e Inventário)
    // Formato: JARDINEIRO <linha> <coluna> <num_ferramentas>
    // Se estiver fora, guardamos -1 -1
    if (jardineiro.estaDentro())
        f << "JARDINEIRO " << jardineiro.getLinha() << " " << jardineiro.getColuna();
    else
        f << "JARDINEIRO -1 -1";

    // Guardar ferramentas da mochila
    vector<Ferramenta*> inventario = jardineiro.getInventario();
    f << " " << inventario.size() << "\n";
    for (Ferramenta* ferr : inventario) {
        // Formato: MOCHILA <tipo> <id>
        f << "MOCHILA " << ferr->getTipo() << " " << ferr->getId() << "\n";
    }

    // 3. PLANTAS
    // Formato: PLANTA <tipo> <linha> <coluna> <agua> <nutrientes> <idade>
    f << "NUM_PLANTAS " << plantas.size() << "\n";
    for (Planta* p : plantas) {
        f << "PLANTA " << p->getTipo() << " "
          << p->getLinha() << " " << p->getColuna() << " "
          << p->getAgua() << " " << p->getNutrientes() << " "
          << p->getIdade() << "\n";
    }

    // 4. FERRAMENTAS NO CHÃO
    f << "NUM_FERRAMENTAS " << ferramentas.size() << "\n";
    for (Ferramenta* ferr : ferramentas) {
        f << "FERRAMENTA " << ferr->getTipo() << " "
          << ferr->getLinha() << " " << ferr->getColuna() << " "
          << ferr->getId() << "\n";
    }

    f.close();
    return true;
}