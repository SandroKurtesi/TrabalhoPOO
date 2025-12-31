

#ifndef TP_ERVADANINHA_H
#define TP_ERVADANINHA_H
#include "../../Planta.h"
#include"../../../Settings.h"


class ErvaDaninha : public Planta {
    int idade = 0;
    int ultimoMultiplicar = 0;

public:
    ErvaDaninha(int l,int c) : Planta( l, c,Settings::ErvaDaninha::inicial_agua,Settings::ErvaDaninha::inicial_nutrientes,Beleza::FEIA) {}

    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo &solo) const override;
    void posReproducao() override {
        ultimoMultiplicar = 0;
    }

    char getRepresentacao() const override { return 'e'; }
    std::string getTipo() const override { return "ErvaDaninha"; }
};


#endif //TP_ERVADANINHA_H