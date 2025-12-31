
#include <fstream>
#include "Simulador.h"
#include "../Ferramentas/tipos/Regador/Regador.h"
#include "../Ferramentas/tipos/Adubo/Adubo.h"
#include "../Ferramentas/tipos/Tesoura/Tesoura.h"
#include "../Ferramentas/tipos/FerramentaZ/FerramentaZ.h"
#include <iostream>
#include <sstream>

using namespace std;

Simulador::~Simulador() {
    delete jardim;
}

void Simulador::iniciar() {
    string linha;
    while (ativo) {
        cout << "> ";
        getline(cin, linha);
        processarComando(linha);
    }
}

void Simulador::processarComando(const string &linha) {
    istringstream iss(linha);
    string cmd;
    iss >> cmd;

    if (cmd == "jardim") {
        if (jardim != nullptr) {
            cout << "Jardim ja existe.\n";
            return;
        }

        int l, c;
        if (iss >> l >> c) {
            if (Jardim::dimensoesValidas(l, c)) {
                jardim = new Jardim(l, c);
                jardim->mostrar();
            } else {
                cout << "Dimensoes invalidas.\n";
            }
        } else {
            cout << "Uso: jardim <linhas> <colunas>\n";
        }
    }
    else if (cmd == "entra") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            for (char &ch : pos) ch = tolower(ch);

            int l = pos[0] - 'a';
            int c = pos[1] - 'a';

            jardim->getJardineiro().entra(l, c, jardim->getLinhas(), jardim->getColunas());
            jardim->verificarFerramentasNoChao();
            jardim->mostrar();
        } else {
            cout << "Uso: entra <lc> (ex: entra ac)\n";
        }
    }
    else if (cmd == "sai") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        if (!jardim->getJardineiro().estaDentro()) {
            cout << "O jardineiro ainda nao entrou no jardim! Use o comando 'entra <lc>'.\n";
            return;
        }
        jardim->getJardineiro().sai();
        jardim->mostrar();
    }
    else if (cmd == "c") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        if (!jardim->getJardineiro().estaDentro()) {
            cout << "O jardineiro ainda nao entrou no jardim! Use o comando 'entra <lc>'.\n";
            return;
        }
        jardim->getJardineiro().moverCima();
        jardim->verificarFerramentasNoChao();
        jardim->mostrar();
    }
    else if (cmd == "b") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        if (!jardim->getJardineiro().estaDentro()) {
            cout << "O jardineiro ainda nao entrou no jardim! Use o comando 'entra <lc>'.\n";
            return;
        }
        jardim->getJardineiro().moverBaixo(jardim->getLinhas());
        jardim->verificarFerramentasNoChao();
        jardim->mostrar();
    }
    else if (cmd == "e") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        if (!jardim->getJardineiro().estaDentro()) {
            cout << "O jardineiro ainda nao entrou no jardim! Use o comando 'entra <lc>'.\n";
            return;
        }
        jardim->getJardineiro().moverEsquerda();
        jardim->verificarFerramentasNoChao();
        jardim->mostrar();
    }
    else if (cmd == "d") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        if (!jardim->getJardineiro().estaDentro()) {
            cout << "O jardineiro ainda nao entrou no jardim! Use o comando 'entra <lc>'.\n";
            return;
        }
        jardim->getJardineiro().moverDireita(jardim->getColunas());
        jardim->verificarFerramentasNoChao();
        jardim->mostrar();
    }
    else if (cmd == "avanca") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        int n = 1;
        if (iss >> n) { /* leu n */ }

        cout << "Avancando " << n << " instante(s)...\n";

        for (int i = 0; i < n; ++i) {
            jardim->avancaInstante();
        }
        jardim->mostrar();
    }

    else if (cmd == "lplantas") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        jardim->listarTodasPlantas();
    }


    else if (cmd == "lplanta") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            int l = tolower(pos[0]) - 'a';
            int c = tolower(pos[1]) - 'a';

            jardim->listarPlanta(l, c);
        } else {
            cout << "Uso: lplanta <lc>\n";
        }
    }


    else if (cmd == "larea") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        jardim->listarArea();
    }
    else if (cmd == "lsolo") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            int l = tolower(pos[0]) - 'a';
            int c = tolower(pos[1]) - 'a';

            int raio = 0;


            iss >> raio;


            jardim->mostrarSolo(l, c, raio);

        } else {
            cout << "Uso: lsolo <lc> [raio] (ex: lsolo aa 2)\n";
        }
    }
    else if (cmd == "lferr") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        const vector<Ferramenta*>& mochila = jardim->getJardineiro().getInventario();

        Ferramenta* ativa = jardim->getJardineiro().getFerramentaNaMao();

        cout << "=== INVENTARIO ===\n";
        if (mochila.empty()) {
            cout << "(Vazio)\n";
        } else {
            for (Ferramenta* f : mochila) {
                cout << " - " << f->getTipo() << " (ID: " << f->getId() << ")";

                if (f == ativa) {
                    cout << " [NA MAO]";
                }
                cout << "\n";
            }
        }
    }
    else if (cmd == "colhe") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            int l = tolower(pos[0]) - 'a';
            int c = tolower(pos[1]) - 'a';


            if (jardim->colherPlanta(l, c)) {
                cout << "Planta colhida com sucesso.\n";
                jardim->mostrar();
            }

        } else {
            cout << "Uso: colhe <lc> (ex: colhe aa)\n";
        }
    }
    else if (cmd == "planta") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string pos, tipo;

        if (iss >> pos >> tipo && pos.size() == 2) {


            int l = tolower(pos[0]) - 'a';
            int c = tolower(pos[1]) - 'a';



            if (jardim->adicionarPlanta(tipo, l, c)) {
                cout << "Planta inserida com sucesso.\n";
                jardim->mostrar();
            } else {
                cout << "Erro: Posicao invalida, ocupada,limite excedido ou tipo desconhecido.\n";
            }
        } else {
            cout << "Uso: planta <lc> <tipo> (ex: planta fb c)\n";
        }
    }
    else if (cmd == "larga") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }


        if (jardim->getJardineiro().getFerramentaNaMao() != nullptr) {
            jardim->getJardineiro().largarFerramenta();
            cout << "Ferramenta guardada na mochila.\n";
        } else {
            cout << "Nao tem nenhuma ferramenta na mao.\n";
        }
    }
    else if (cmd == "pega") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        int id;
        if (iss >> id) {

            if (jardim->getJardineiro().pegarFerramenta(id)) {
                cout << "Ferramenta " << id << " esta agora na mao.\n";
            } else {
                cout << "Erro: Ferramenta " << id << " nao encontrada no inventario.\n";
            }
        } else {
            cout << "Uso: pega <id> (ex: pega 1)\n";
        }
    }
    else if (cmd == "compra") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string tipo;
        if (iss >> tipo) {
            Ferramenta* nova = nullptr;


            if (tipo == "regador" || tipo == "g") {
                nova = new Regador();
            }
            else if (tipo == "adubo" || tipo == "a") {
                nova = new Adubo();
            }
            else if (tipo == "tesoura" || tipo == "t") {
                nova = new Tesoura();
            }
            else if (tipo == "z") {
                nova = new FerramentaZ();
            }

            if (nova != nullptr) {

                jardim->getJardineiro().guardarFerramenta(nova);
                cout << "Ferramenta " << nova->getTipo() << " comprada e guardada no inventario.\n";
            } else {
                cout << "Tipo de ferramenta invalido (g, a, t, z).\n";
            }
        } else {
            cout << "Uso: compra <tipo> (ex: compra a)\n";
        }
    }
    else if (cmd == "grava") {
        if (!jardim) {
            cout << "Nao ha jardim para gravar.\n";
            return;
        }

        string nome;
        iss >> nome;

        if (nome.empty()) {
            cout << "Erro: Indique o nome da gravacao (ex: grava teste)\n";
        } else {

            copias[nome] = jardim->getEstadoComoString();
            cout << "Jardim gravado em memoria com o nome '" << nome << "'.\n";
        }
    }
    else if (cmd == "recupera") {
        string nome;
        iss >> nome;

        if (nome.empty()) {
            cout << "Erro: Indique o nome da gravacao (ex: recupera checkpoint)\n";
        } else {

            if (copias.find(nome) != copias.end()) {


                if (!jardim) {
                    stringstream ss(copias[nome]);
                    string t; int l, c;
                    ss >> t >> l >> c;
                    jardim = new Jardim(l, c);
                }


                if (jardim->carregarEstado(copias[nome])) {
                    cout << "Jogo recuperado de '" << nome << "'.\n";


                    copias.erase(nome);

                    jardim->mostrar();
                } else {
                    cout << "Erro ao carregar o estado.\n";
                }
            } else {
                cout << "Erro: Gravacao '" << nome << "' nao encontrada em memoria.\n";
            }
        }
    }
    else if (cmd == "apaga") {
        string nome;
        iss >> nome;

        if (nome.empty()) {
            cout << "Erro: Indique o nome da gravacao a apagar (ex: apaga save1)\n";
        }
        else {

            if (copias.erase(nome) > 0) {
                cout << "A copia do jardim '" << nome << "' foi apagada da memoria.\n";
            } else {
                cout << "Erro: Nao existe nenhuma copia com o nome '" << nome << "'.\n";
            }
        }
    }
    else if (cmd == "executa") {
        string nomeFicheiro;
        if (iss >> nomeFicheiro) {
            ifstream ficheiro(nomeFicheiro);

            if (ficheiro.is_open()) {
                cout << "A executar comandos do ficheiro '" << nomeFicheiro << "'...\n";
                string linhaFicheiro;

                while (getline(ficheiro, linhaFicheiro)) {

                    if (linhaFicheiro.empty() || linhaFicheiro[0] == '#') continue;

                    cout << ">> " << linhaFicheiro << "\n";
                    processarComando(linhaFicheiro);
                }
                ficheiro.close();
                cout << "Execucao do ficheiro terminada.\n";
            } else {
                cout << "Erro: Nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'.\n";
            }
        } else {
            cout << "Uso: executa <nome-do-ficheiro>\n";
        }
    }
    else if (cmd == "fim") {
        ativo = false;
        cout << "Encerrando simulador...\n";
    }
    else if (cmd.empty()) {

    }
    else {
        cout << "Comando desconhecido: '" << cmd << "'\n";
    }
}