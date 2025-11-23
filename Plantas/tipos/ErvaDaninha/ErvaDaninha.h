

#ifndef TP_ERVADANINHA_H
#define TP_ERVADANINHA_H
#include "../../Planta.h"


class ErvaDaninha : public Planta {
    int idade = 0;
    int ultimoMultiplicar = 0;

public:
    ErvaDaninha() : Planta(5, 5, Beleza::FEIA) {}

    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo &solo) const override;

    char getRepresentação() const override { return 'e'; }
    std::string getTipo() const override { return "ErvaDaninha"; }
};


#endif //TP_ERVADANINHA_H