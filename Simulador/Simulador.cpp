

#include "Simulador.h"
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
        jardim->getJardineiro().sai();
        jardim->mostrar();
    }
    else if (cmd == "c") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        jardim->getJardineiro().moverCima();
        jardim->mostrar();
    }
    else if (cmd == "b") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        jardim->getJardineiro().moverBaixo(jardim->getLinhas());
        jardim->mostrar();
    }
    else if (cmd == "e") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        jardim->getJardineiro().moverEsquerda();
        jardim->mostrar();
    }
    else if (cmd == "d") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        jardim->getJardineiro().moverDireita(jardim->getColunas());
        jardim->mostrar();
    }
    else if (cmd == "avanca") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        int n = 1;
        if (iss >> n) {
            if (n <= 0) {
                cout << "Numero de instantes deve ser positivo.\n";
                return;
            }
        }
        cout << "Comando 'avanca' reconhecido, avancando " << n << " instante(s). Ainda nao implementado.\n";
    }
    else if (cmd == "lplantas") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        cout << "Comando 'lplantas' reconhecido, nao implementado ainda.\n";
    }
    else if (cmd == "lplanta") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            cout << "Comando 'lplanta' reconhecido para posicao " << pos << ", nao implementado ainda.\n";
        } else {
            cout << "Uso: lplanta <lc> (ex: lplanta ej)\n";
        }
    }
    else if (cmd == "larea") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        cout << "Comando 'larea' reconhecido, nao implementado ainda.\n";
    }
    else if (cmd == "lsolo") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string pos;
        int n = 0;
        if (iss >> pos && pos.size() == 2) {
            iss >> n; // n eh opcional
            cout << "Comando 'lsolo' reconhecido para posicao " << pos;
            if (n > 0) cout << " com raio " << n;
            cout << ", nao implementado ainda.\n";
        } else {
            cout << "Uso: lsolo <lc> [n] (ex: lsolo df 2)\n";
        }
    }
    else if (cmd == "lferr") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        cout << "Comando 'lferr' reconhecido, nao implementado ainda.\n";
    }
    else if (cmd == "colhe") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            cout << "Comando 'colhe' reconhecido para posicao " << pos << ", nao implementado ainda.\n";
        } else {
            cout << "Uso: colhe <lc> (ex: colhe fb)\n";
        }
    }
    else if (cmd == "planta") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string pos, tipo;
        // Lê a posição (ex: "aa") e o tipo (ex: "r")
        if (iss >> pos >> tipo && pos.size() == 2) {

            // Converter as letras em coordenadas (a->0, b->1, etc.)
            // Usamos tolower para funcionar com 'A' ou 'a'
            int l = tolower(pos[0]) - 'a';
            int c = tolower(pos[1]) - 'a';

            // Tenta adicionar a planta no Jardim
            // A função adicionarPlanta já verifica se a posição é válida
            // e se o tipo existe.
            if (jardim->adicionarPlanta(tipo, l, c)) {
                cout << "Planta inserida com sucesso.\n";
                jardim->mostrar(); // Mostra o jardim atualizado logo de seguida
            } else {
                cout << "Erro: Posicao invalida, ocupada ou tipo desconhecido.\n";
            }
        } else {
            cout << "Uso: planta <lc> <tipo> (ex: planta fb c)\n";
        }
    }
    else if (cmd == "larga") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }
        cout << "Comando 'larga' reconhecido, nao implementado ainda.\n";
    }
    else if (cmd == "pega") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        int n;
        if (iss >> n) {
            cout << "Comando 'pega' reconhecido para ferramenta " << n << ", nao implementado ainda.\n";
        } else {
            cout << "Uso: pega <n> (ex: pega 7)\n";
        }
    }
    else if (cmd == "compra") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string tipo;
        if (iss >> tipo && tipo.size() == 1) {
            char t = tolower(tipo[0]);
            if (t == 'g' || t == 'a' || t == 't' || t == 'z') {
                cout << "Comando 'compra' reconhecido para ferramenta " << t << ", nao implementado ainda.\n";
            } else {
                cout << "Tipo de ferramenta invalido. Use: g, a, t ou z\n";
            }
        } else {
            cout << "Uso: compra <c> (ex: compra a)\n";
        }
    }
    else if (cmd == "grava") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string nome;
        if (iss >> nome) {
            cout << "Comando 'grava' reconhecido para nome '" << nome << "', nao implementado ainda.\n";
        } else {
            cout << "Uso: grava <nome>\n";
        }
    }
    else if (cmd == "recupera") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string nome;
        if (iss >> nome) {
            cout << "Comando 'recupera' reconhecido para nome '" << nome << "', nao implementado ainda.\n";
        } else {
            cout << "Uso: recupera <nome>\n";
        }
    }
    else if (cmd == "apaga") {
        if (!jardim) {
            cout << "Crie primeiro o jardim.\n";
            return;
        }

        string nome;
        if (iss >> nome) {
            cout << "Comando 'apaga' reconhecido para nome '" << nome << "', nao implementado ainda.\n";
        } else {
            cout << "Uso: apaga <nome>\n";
        }
    }
    else if (cmd == "executa") {

        string ficheiro;
        if (iss >> ficheiro) {
            cout << "Comando 'executa' reconhecido para ficheiro '" << ficheiro << "', nao implementado ainda.\n";
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