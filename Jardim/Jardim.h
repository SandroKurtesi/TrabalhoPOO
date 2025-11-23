

#ifndef TP_JARDIM_H
#define TP_JARDIM_H

#include "../Solo/Solo.h"
#include "../Jardineiro/Jardineiro.h"
#include <iostream>

class Jardim {
    int linhas;
    int colunas;
    Solo** grelha;
    Jardineiro jardineiro;

public:
    Jardim(int l, int c);
    ~Jardim();

    static bool dimensoesValidas(int l, int c);

    void mostrar() const;
    Jardineiro& getJardineiro();

    int getLinhas() const;
    int getColunas() const;

};

#endif //TP_JARDIM_H
