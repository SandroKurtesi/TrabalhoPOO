

#ifndef TP_JARDINEIRO_H
#define TP_JARDINEIRO_H

#include <iostream>
#include <vector>
#include "../Ferramentas/Ferramenta.h"
#include "../Settings.h"

class Jardineiro {
    int linha = -1, coluna = -1;
    bool dentro = false;

    std::vector<Ferramenta*> inventario;
    Ferramenta* ferramentaNaMao = nullptr;


    int movimentosTurno = 0;
    int colheitasNesteTurno = 0;
    int plantacoesTurno = 0;
    int entradasTurno = 0;
    int saidasTurno = 0;

public:
    Jardineiro() = default;

    bool estaDentro() const;
    int getLinha() const;
    int getColuna() const;

    void entra(int l, int c, int maxLinhas, int maxColunas);
    void sai();

    void moverCima();
    void moverBaixo(int maxLinhas);
    void moverEsquerda();
    void moverDireita(int maxColunas);

    char getRepresentacao() const { return '*'; }

    void guardarFerramenta(Ferramenta* f);
    const std::vector<Ferramenta*>& getInventario() const;


    bool pegarFerramenta(int id);
    void largarFerramenta();


    void removerFerramentaDaMao();

    Ferramenta* getFerramentaNaMao() const { return ferramentaNaMao; }

    bool podeColher() const ;
    void registarColheita() ;


    void resetTurno() ;
    void limparMochila() {
        for (Ferramenta* f : inventario) {
            delete f;
        }
        inventario.clear();
        ferramentaNaMao = nullptr;
    }

    bool podeMover() const;
    void registarMovimento();


    bool podePlantar() const;
    void registarPlantacao();

    bool podeEntrar() const;
    void registarEntrada();

    bool podeSair() const;
    void registarSaida();

};

#endif //TP_JARDINEIRO_H
