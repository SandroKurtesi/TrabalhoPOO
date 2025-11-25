

#ifndef TP_PLANTAEXOTICA_H
#define TP_PLANTAEXOTICA_H
#include "../../Planta.h"
#include "../../../Settings.h"


class PlantaExotica : public Planta {

public:
    PlantaExotica(int l, int c)
            : Planta(l, c, 10, 10, Beleza::BONITA)
    {}

    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo &solo) const override;

    char getRepresentacao() const override { return 'x'; }
    std::string getTipo() const override { return "PlantaExotica"; }
};


#endif //TP_PLANTAEXOTICA_H