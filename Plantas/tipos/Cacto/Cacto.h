

#ifndef TP_CACTO_H
#define TP_CACTO_H
#include "../../Planta.h"
#include"../../../Settings.h"


class Cacto : public Planta {
    int instantesComSoloMolhado = Settings::Cacto::morre_agua_solo_instantes;
    int instantesSemNutrientes = Settings::Cacto::morre_nutrientes_solo_instantes;

public:
    Cacto(int l, int c)
            : Planta(l, c, 0, 0, Beleza::NEUTRA)
    {}

    void atualizar(Solo &solo) override;
    bool podemMultiplicar(const Solo &solo) const override;

    char getRepresentacao() const override { return 'c'; }
    std::string getTipo() const override { return "Cacto"; }
};


#endif //TP_CACTO_H