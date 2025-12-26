#ifndef FERRAMENTAZ_H
#define FERRAMENTAZ_H

#include "../../Ferramenta.h"
#include <string>

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ(int l=-1, int c=-1);

    // A Ação Principal
    void usar(Solo &solo) override;

    // --- O QUE FALTAVA ---
    // Define o simbolo que aparece no mapa quando a ferramenta esta no chao
    char getRepresentacao() const override { return 'Z'; }

    // Identificador
    std::string getTipo() const override { return "FerramentaZ"; }
};

#endif // FERRAMENTAZ_H