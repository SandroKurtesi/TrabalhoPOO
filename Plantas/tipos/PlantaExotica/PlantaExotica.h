#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "../../Planta.h"
#include <string>

class PlantaExotica : public Planta {
public:

    PlantaExotica(int l, int c);



    char getRepresentacao() const override { return 'P'; }


    Planta* duplica(int l, int c) const ;
    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo& solo) const override;
    std::string getTipo() const override { return "PlantaExotica"; }
};

#endif // PLANTAEXOTICA_H