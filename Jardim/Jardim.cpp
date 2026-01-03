#include "Jardim.h"
#include <iostream>
#include <sstream>


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


Jardim::Jardim(int l, int c) : linhas(l), colunas(c) {
    grelha = new Solo*[linhas];
    for (int i = 0; i < linhas; ++i)
        grelha[i] = new Solo[colunas];
    for (int i = 0; i < 3; i++) {
        spawnFerramentaAleatoria();
    }
}


Jardim::~Jardim() {

    for (int i = 0; i < linhas; ++i)
        delete[] grelha[i];
    delete[] grelha;


    for (Planta* p : plantas) {
        delete p;
    }
    plantas.clear();

    for (Ferramenta* f : ferramentas) {
        delete f;
    }
    ferramentas.clear();
}


Jardineiro &Jardim::getJardineiro() { return jardineiro; }
int Jardim::getLinhas() const { return linhas; }
int Jardim::getColunas() const { return colunas; }
bool Jardim::dimensoesValidas(int l, int c) { return l > 0 && l <= 26 && c > 0 && c <= 26; }

std::string Jardim::getEstadoComoString() const {
    std::stringstream ss;

    ss << "JARDIM " << linhas << " " << colunas << "\n";


    if (jardineiro.estaDentro())
        ss << "JARDINEIRO " << jardineiro.getLinha() << " " << jardineiro.getColuna();
    else
        ss << "JARDINEIRO -1 -1";

    const auto& inventario = jardineiro.getInventario();
    ss << " " << inventario.size() << "\n";
    for (Ferramenta* f : inventario) {
        ss << "MOCHILA " << f->getTipo() << " " << f->getId() << "\n";
    }


    ss << "NUM_PLANTAS " << plantas.size() << "\n";
    for (Planta* p : plantas) {
        ss << "PLANTA " << p->getTipo() << " "
           << p->getLinha() << " " << p->getColuna() << " "
           << p->getAgua() << " " << p->getNutrientes() << " "
           << p->getIdade() << "\n";
    }


    ss << "NUM_FERRAMENTAS " << ferramentas.size() << "\n";
    for (Ferramenta* f : ferramentas) {
        ss << "FERRAMENTA " << f->getTipo() << " "
           << f->getLinha() << " " << f->getColuna() << " "
           << f->getId() << "\n";
    }
    ss << "DADOS_SOLO " << linhas * colunas << "\n";
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            ss << "SOLO " << i << " " << j << " "
               << grelha[i][j].getAgua() << " "
               << grelha[i][j].getNutrientes() << "\n";
        }
    }

    return ss.str();
}


void Jardim::spawnFerramentaAleatoria() {

    if (ferramentas.size() >= linhas * colunas) return;

    int l, c;
    bool ocupada;


    do {
        l = rand() % linhas;
        c = rand() % colunas;
        ocupada = false;


        for (Ferramenta* f : ferramentas) {
            if (f->getLinha() == l && f->getColuna() == c) {
                ocupada = true;
                break;
            }
        }
    } while (ocupada);


    int tipo = rand() % 4;
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


        if (f->getLinha() == jardineiro.getLinha() && f->getColuna() == jardineiro.getColuna()) {

            cout << "Encontraste uma ferramenta: " << f->getTipo() << " (ID: " << f->getId() << ")!\n";


            jardineiro.guardarFerramenta(f);


            it = ferramentas.erase(it);


            spawnFerramentaAleatoria();

        } else {
            ++it;
        }
    }
}



bool Jardim::adicionarPlanta(const std::string& tipo, int l, int c) {

    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        return false;
    }

    if (!jardineiro.podePlantar()) {
        cout << "O jardineiro nao pode plantar mais neste turno (Max 2).\n";
        return false;
    }


    for (Planta* p : plantas) {
        if (p->getLinha() == l && p->getColuna() == c) {
            return false;
        }
    }


    Planta* nova = nullptr;


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


    if (nova != nullptr) {
        plantas.push_back(nova);
        jardineiro.registarPlantacao();
        return true;
    }

    return false;
}






void Jardim::mostrar() const {

    cout << "  ";
    for (int j = 0; j < colunas; ++j) {
        cout << char('A' + j);
    }
    cout << "\n";


    for (int i = 0; i < linhas; ++i) {


        cout << char('A' + i) << " ";


        for (int j = 0; j < colunas; ++j) {

            bool desenhou = false;


            if (jardineiro.estaDentro() && i == jardineiro.getLinha() && j == jardineiro.getColuna()) {
                cout << jardineiro.getRepresentacao();
                desenhou = true;
            }


            if (!desenhou) {
                for (Planta* p : plantas) {
                    if (p->getLinha() == i && p->getColuna() == j) {
                        cout << p->getRepresentacao();
                        desenhou = true;
                        break;
                    }
                }
            }


            if (!desenhou) {
                for (Ferramenta* f : ferramentas) {
                    if (f->getLinha() == i && f->getColuna() == j) {
                        cout << f->getRepresentacao();
                        desenhou = true;
                        break;
                    }
                }
            }


            if (!desenhou) {
                cout << grelha[i][j].getRepresentacao();
            }
        }

        cout << "\n";
    }
}
void Jardim::infoSolo(int l, int c) const {

    if (l < 0 || l >= linhas || c < 0 || c >= colunas) {
        cout << "Coordenadas invalidas.\n";
        return;
    }


    Solo& s = grelha[l][c];
    cout << "--- INFO SOLO (" << char('A' + l) << char('A' + c) << ") ---\n";
    cout << "Agua: " << s.getAgua() << " | Nutrientes: " << s.getNutrientes() << "\n";


    cout << "Ocupantes:\n";


    if (jardineiro.estaDentro() && jardineiro.getLinha() == l && jardineiro.getColuna() == c) {
        cout << " - [JARDINEIRO]\n";
    }


    for (Planta* p : plantas) {
        if (p->getLinha() == l && p->getColuna() == c) {
            cout << " - [PLANTA] " << p->getTipo() << " (" << p->getRepresentacao() << ")\n";

        }
    }


    for (Ferramenta* f : ferramentas) {
        if (f->getLinha() == l && f->getColuna() == c) {
            cout << " - [FERRAMENTA] " << f->getTipo() << " (ID: " << f->getId() << ")\n";
        }
    }
}

bool Jardim::colherPlanta(int l, int c) {

    if (l < 0 || l >= linhas || c < 0 || c >= colunas) return false;


    if (!jardineiro.podeColher()) {
        cout << "O jardineiro esta cansado! (Max 5 colheitas por turno)\n";
        return false;
    }


    for (auto it = plantas.begin(); it != plantas.end(); ++it) {
        Planta* p = *it;

        if (p->getLinha() == l && p->getColuna() == c) {



            delete p;


            plantas.erase(it);


            jardineiro.registarColheita();

            return true;
        }
    }

    cout << "Nao ha planta nessa posicao.\n";
    return false;
}




int Jardim::contarVizinhosOcupados(int l, int c) {
    int contador = 0;
    int dL[] = {-1, 1, 0, 0};
    int dC[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int vL = l + dL[i];
        int vC = c + dC[i];


        if (vL >= 0 && vL < linhas && vC >= 0 && vC < colunas) {

            for (Planta* p : plantas) {
                if (p->getLinha() == vL && p->getColuna() == vC) {
                    contador++;
                    break;
                }
            }
        }
    }
    return contador;
}


void Jardim::avancaInstante() {

    jardineiro.resetTurno();




    vector<Planta*> novasPlantas;


    if (jardineiro.estaDentro()) {
        Ferramenta* f = jardineiro.getFerramentaNaMao();

        if (f != nullptr) {

            if (f->getTipo() == "Tesoura") {

                Tesoura* t = (Tesoura*) f;

                bool cortou = false;


                for (Planta* p : plantas) {
                    if (p->getLinha() == jardineiro.getLinha() &&
                        p->getColuna() == jardineiro.getColuna()) {


                        if (t->tentarCortar(p)) {
                            removerPlanta(p->getLinha(), p->getColuna());
                            cortou = true;
                        }
                        break;
                    }
                }
            }

            else {

                f->usar(grelha[jardineiro.getLinha()][jardineiro.getColuna()]);


                bool lixo = false;

                if (f->getTipo() == "Regador") {
                    Regador* r = (Regador*)f;

                    if (r->getAgua() <= 0) lixo = true;
                }
                else if (f->getTipo() == "Adubo") {
                    Adubo* a = (Adubo*)f;

                    if (a->getQuantidade() <= 0) lixo = true;
                }

                if (lixo) {
                    cout << "A ferramenta " << f->getTipo() << " acabou e foi deitada fora!\n";
                    jardineiro.removerFerramentaDaMao();
                    delete f;
                }
            }
        }
    }

    auto it = plantas.begin();
    while (it != plantas.end()) {
        Planta* mae = *it;


        Solo& soloMae = grelha[mae->getLinha()][mae->getColuna()];


        mae->atualizar(soloMae);

        bool morreuPorVizinhos = false;
        if (mae->getTipo() == "Roseira") {
            int vizinhos = contarVizinhosOcupados(mae->getLinha(), mae->getColuna());


            int maxVizinhosPossiveis = 0;
            int dL[] = {-1, 1, 0, 0}; int dC[] = {0, 0, -1, 1};
            for(int i=0; i<4; i++) {
                int vvL = mae->getLinha() + dL[i]; int vvC = mae->getColuna() + dC[i];
                if(vvL >= 0 && vvL < linhas && vvC >= 0 && vvC < colunas) maxVizinhosPossiveis++;
            }


            if (vizinhos == maxVizinhosPossiveis && maxVizinhosPossiveis > 0) {
                morreuPorVizinhos = true;
                cout << "A Roseira sufocou com os vizinhos!\n";

                soloMae.setNutrientes(soloMae.getNutrientes() + mae->getNutrientes()/2);
                soloMae.setAgua(soloMae.getAgua() + mae->getAgua()/2);
            }
        }


        if (!mae->estaViva() || morreuPorVizinhos) {

            if (!morreuPorVizinhos) {
                cout << "Planta " << mae->getRepresentacao() << " morreu na posicao "
                     << (char)('A' + mae->getLinha()) << (char)('A' + mae->getColuna()) << ".\n";
            }

            delete mae;
            it = plantas.erase(it);
            continue;
        }


        if (mae->podemMultiplicar(soloMae)) {

            int filhoL = -1;
            int filhoC = -1;
            bool localEncontrado = false;


            if (mae->getTipo() == "ErvaDaninha") {
                int start = rand() % 4;
                int dL[] = {-1, 1, 0, 0};
                int dC[] = {0, 0, -1, 1};

                for(int i=0; i<4; i++) {
                    int idx = (start + i) % 4;
                    int tL = mae->getLinha() + dL[idx];
                    int tC = mae->getColuna() + dC[idx];


                    if (tL >= 0 && tL < linhas && tC >= 0 && tC < colunas) {
                        filhoL = tL;
                        filhoC = tC;
                        removerPlanta(filhoL, filhoC);
                        localEncontrado = true;
                        break;
                    }
                }
            }

            else {
                if (getVizinhaLivre(mae->getLinha(), mae->getColuna(), filhoL, filhoC)) {
                    localEncontrado = true;
                }
            }


            if (localEncontrado) {
                Planta* bebe = nullptr;
                string tipo = mae->getTipo();

                if (tipo == "Roseira") {
                    bebe = new Roseira(filhoL, filhoC);
                    int aguaTotal = mae->getAgua();
                    mae->setNutrientes(Settings::Roseira::original_nutrientes);
                    int aguaMae = (aguaTotal * Settings::Roseira::original_agua_percentagem) / 100;
                    mae->setAgua(aguaMae);
                    bebe->setNutrientes(Settings::Roseira::nova_nutrientes);
                    int aguaBebe = (aguaTotal * Settings::Roseira::nova_agua_percentagem) / 100;
                    bebe->setAgua(aguaBebe);
                }
                else if (tipo == "Cacto") {
                    bebe = new Cacto(filhoL, filhoC);
                    int aguaMae = mae->getAgua();
                    int nutrMae = mae->getNutrientes();
                    mae->setAgua(aguaMae / 2);
                    mae->setNutrientes(nutrMae / 2);
                    bebe->setAgua(aguaMae / 2);
                    bebe->setNutrientes(nutrMae / 2);
                }
                else if (tipo == "ErvaDaninha") {
                    bebe = new ErvaDaninha(filhoL, filhoC);
                    bebe->setNutrientes(Settings::ErvaDaninha::nova_nutrientes);
                    bebe->setAgua(5);
                }
                else if (tipo == "PlantaExotica") {
                    bebe = new PlantaExotica(filhoL, filhoC);
                    int metadeNutr = mae->getNutrientes() / 2;
                    bebe->setNutrientes(metadeNutr);
                    mae->setNutrientes(metadeNutr);
                    bebe->setAgua(mae->getAgua());
                }

                if (bebe != nullptr) {
                    novasPlantas.push_back(bebe);
                    cout << "Nova " << tipo << " nasceu/invadiu em "
                         << (char)('A' + filhoL) << (char)('A' + filhoC) << "!\n";
                    mae->posReproducao();
                }
            }
        }

        ++it;
    }


    for (Planta* p : novasPlantas) {
        plantas.push_back(p);
    }
}


void Jardim::listarTodasPlantas() const {
    cout << "=== LISTA DE PLANTAS DO JARDIM ===\n";
    if (plantas.empty()) {
        cout << "(Nenhuma planta no jardim)\n";
        return;
    }

    for (const Planta* p : plantas) {

        cout << " - " << p->getDescricao() << "\n";


        const Solo& s = grelha[p->getLinha()][p->getColuna()];
        cout << "   [Solo] Agua: " << s.getAgua() << " Nutr: " << s.getNutrientes() << "\n";
    }
}


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

        }
    }

    if (!encontrou) {
        cout << "Nao existe nenhuma planta na posicao "
             << (char)('A' + l) << (char)('A' + c) << ".\n";
    }
}


void Jardim::listarArea() const {
    cout << "=== LISTAGEM DA AREA NAO-VAZIA ===\n";

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            bool temAlgo = false;


            if (jardineiro.estaDentro() && jardineiro.getLinha() == i && jardineiro.getColuna() == j)
                temAlgo = true;


            if (!temAlgo) {
                for (auto p : plantas)
                    if (p->getLinha() == i && p->getColuna() == j) { temAlgo = true; break; }
            }


            if (!temAlgo) {
                for (auto f : ferramentas)
                    if (f->getLinha() == i && f->getColuna() == j) { temAlgo = true; break; }
            }


            if (temAlgo) {
                infoSolo(i, j);
                cout << "-----------------------------\n";
            }
        }
    }
}


bool Jardim::getVizinhaLivre(int l, int c, int& resL, int& resC) {

    int dL[] = {-1, 1, 0, 0};
    int dC[] = {0, 0, -1, 1};


    int start = rand() % 4;

    for (int i = 0; i < 4; i++) {
        int idx = (start + i) % 4;

        int vizL = l + dL[idx];
        int vizC = c + dC[idx];


        if (vizL >= 0 && vizL < linhas && vizC >= 0 && vizC < colunas) {


            bool ocupado = false;
            for (Planta* p : plantas) {
                if (p->getLinha() == vizL && p->getColuna() == vizC) {
                    ocupado = true;
                    break;
                }
            }


            if (!ocupado) {
                resL = vizL;
                resC = vizC;
                return true;
            }
        }
    }
    return false;
}

void Jardim::removerPlanta(int l, int c) {
    auto it = plantas.begin();
    while (it != plantas.end()) {
        Planta* p = *it;
        if (p->getLinha() == l && p->getColuna() == c) {
            delete p;
            it = plantas.erase(it);
            return;
        } else {
            ++it;
        }
    }
    cout << "Nenhuma planta para cortar aqui.\n";
}



bool Jardim::carregarEstado(const string& estado) {
    stringstream ss(estado);
    string tag;
    int linhasLidas, colunasLidas;


    if (!(ss >> tag >> linhasLidas >> colunasLidas)) return false;


    if (linhasLidas != linhas || colunasLidas != colunas) {
        for (int i = 0; i < linhas; ++i) delete[] grelha[i];
        delete[] grelha;

        linhas = linhasLidas;
        colunas = colunasLidas;

        grelha = new Solo*[linhas];
        for (int i = 0; i < linhas; ++i) grelha[i] = new Solo[colunas];
    }


    for (Planta* p : plantas) delete p;
    plantas.clear();

    for (Ferramenta* f : ferramentas) delete f;
    ferramentas.clear();

    jardineiro.limparMochila();


    int jLin, jCol;
    ss >> tag >> jLin >> jCol;
    if (jLin != -1) jardineiro.entra(jLin, jCol, linhas, colunas);
    else jardineiro.sai();

    int numItems;
    ss >> numItems;
    for (int i = 0; i < numItems; i++) {
        string tipo; int id;
        ss >> tag >> tipo >> id;

        Ferramenta* nova = nullptr;
        if (tipo == "Adubo") nova = new Adubo();
        else if (tipo == "Regador") nova = new Regador();
        else if (tipo == "Tesoura") nova = new Tesoura();
        else if (tipo == "FerramentaZ") nova = new FerramentaZ();

        if (nova) {
            nova->setId(id);
            jardineiro.guardarFerramenta(nova);
        }
    }


    int numPlantas;
    ss >> tag >> numPlantas;
    for (int i = 0; i < numPlantas; i++) {
        string tipo;
        int l, c, agua, nutr, idade;
        ss >> tag >> tipo >> l >> c >> agua >> nutr >> idade;

        Planta* p = nullptr;
        if (tipo == "Roseira") p = new Roseira(l, c);
        else if (tipo == "Cacto") p = new Cacto(l, c);
        else if (tipo == "ErvaDaninha") p = new ErvaDaninha(l, c);
        else if (tipo == "PlantaExotica") p = new PlantaExotica(l, c);

        if (p) {
            p->setAgua(agua);
            p->setNutrientes(nutr);
            p->setIdade(idade);
            plantas.push_back(p);
        }
    }


    int numFerr;
    ss >> tag >> numFerr;
    for (int i = 0; i < numFerr; i++) {
        string tipo; int l, c, id;
        ss >> tag >> tipo >> l >> c >> id;

        Ferramenta* f = nullptr;
        if (tipo == "Adubo") f = new Adubo(l, c);
        else if (tipo == "Regador") f = new Regador(l, c);
        else if (tipo == "Tesoura") f = new Tesoura(l, c);
        else if (tipo == "FerramentaZ") f = new FerramentaZ(l, c);

        if (f) {
            f->setId(id);
            ferramentas.push_back(f);
        }
    }

    int numCelulas;
    ss >> tag >> numCelulas;
    for (int i = 0; i < numCelulas; i++) {
        int l, c, agua, nutr;
        ss >> tag >> l >> c >> agua >> nutr;

        if (l >= 0 && l < linhas && c >= 0 && c < colunas) {
            grelha[l][c].setAgua(agua);
            grelha[l][c].setNutrientes(nutr);
        }
    }

    return true;
}

void Jardim::mostrarSolo(int l, int c, int raio) {

    if (raio <= 0) {
        infoSolo(l, c);
        return;
    }

    cout << "--- INFO SOLO COM RAIO " << raio << " CENTRADO EM "
         << (char)('A' + l) << (char)('A' + c) << " ---\n";


    int inicioL = (l - raio < 0) ? 0 : l - raio;
    int fimL    = (l + raio >= linhas) ? linhas - 1 : l + raio;
    int inicioC = (c - raio < 0) ? 0 : c - raio;
    int fimC    = (c + raio >= colunas) ? colunas - 1 : c + raio;

    for (int i = inicioL; i <= fimL; i++) {
        for (int j = inicioC; j <= fimC; j++) {
            infoSolo(i, j);
            cout << "-----------------------------\n";
        }
    }
}