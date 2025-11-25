

#ifndef TP_JARDIM_H
#define TP_JARDIM_H

#include "../Solo/Solo.h"
#include "../Jardineiro/Jardineiro.h"
#include <iostream>
#include <vector>

#include "../Plantas/Planta.h"

class Jardim {
    int linhas;
    int colunas;
    Solo** grelha;
    Jardineiro jardineiro;

    std::vector<Planta*> plantas;

public:
    Jardim(int l, int c);
    ~Jardim();

    static bool dimensoesValidas(int l, int c);



    bool adicionarPlanta(const std::string& tipo, int l, int c);

    void mostrar() const;
    Jardineiro& getJardineiro();


    int getLinhas() const;
    int getColunas() const;

};

#endif //TP_JARDIM_H
