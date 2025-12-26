#ifndef PLANTAEXOTICA_H
#define PLANTAEXOTICA_H

#include "../../Planta.h"
#include <string>

class PlantaExotica : public Planta {
public:
    // Construtor
    PlantaExotica(int l, int c);

    // --- MÉTODOS OBRIGATÓRIOS (OVERRIDES) ---

    char getRepresentacao() const override { return 'P'; }

    // Os outros métodos que já tinhas:
    Planta* duplica(int l, int c) const ;
    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo& solo) const override;
    std::string getTipo() const override { return "PlantaExotica"; }
};

#endif // PLANTAEXOTICA_H