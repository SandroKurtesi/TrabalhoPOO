

#ifndef TP_CACTO_H
#define TP_CACTO_H
#include "../../Planta.h"


class Cacto : public Planta {
    int instantesComSoloMolhado = 0;
    int instantesSemNutrientes = 0;

public:
    Cacto() : Planta(0, 0, Beleza::NEUTRA) {}

    void atualizar(Solo &solo) override;
    bool podemMultiplicar(const Solo &solo) const override;

    char getRepresentação() const override { return 'c'; }
    std::string getTipo() const override { return "Cacto"; }
};


#endif //TP_CACTO_H