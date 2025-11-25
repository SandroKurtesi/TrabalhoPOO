

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
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        string pos;
        if (iss >> pos && pos.size() == 2) {
            int l = tolower(pos[0]) - 'a';
            int c = tolower(pos[1]) - 'a';

            // Chama a função do Jardim
            jardim->infoSolo(l, c);

        } else {
            cout << "Uso: lsolo <lc> (ex: lsolo aa)\n";
        }
    }
    else if (cmd == "lferr") {
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        const vector<Ferramenta*>& mochila = jardim->getJardineiro().getInventario();
        // Obter a ferramenta ativa para comparar
        Ferramenta* ativa = jardim->getJardineiro().getFerramentaNaMao();

        cout << "=== INVENTARIO ===\n";
        if (mochila.empty()) {
            cout << "(Vazio)\n";
        } else {
            for (Ferramenta* f : mochila) {
                cout << " - " << f->getTipo() << " (ID: " << f->getId() << ")";

                // Se for a ferramenta ativa, mostra indicação
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

            // Chama a função do Jardim
            if (jardim->colherPlanta(l, c)) {
                cout << "Planta colhida com sucesso.\n";
                jardim->mostrar();
            }
            // (A função colherPlanta já imprime mensagens de erro especificas,
            // por isso não precisamos de muitos couts aqui)
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
        if (!jardim) { cout << "Crie primeiro o jardim.\n"; return; }

        // Verifica se tem algo para largar
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
            // Chama a função do Jardineiro
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

            // Factory de Ferramentas (igual à do Jardim)
            if (tipo == "regador" || tipo == "g") {
                nova = new Regador(); // Sem coordenadas = vai para o inventário
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
                // --- AQUI ESTÁ A LIGAÇÃO ---
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