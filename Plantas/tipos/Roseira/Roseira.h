

#ifndef TP_ROSEIRA_H
#define TP_ROSEIRA_H
#include "../../Planta.h"


class Roseira :public Planta {
public:
    Roseira() : Planta(25, 25, Beleza::BONITA) {}

    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo &solo) const override;

    char getRepresentação() const override { return 'r'; }
    std::string getTipo() const override { return "Roseira"; }
};


#endif //TP_ROSEIRA_H