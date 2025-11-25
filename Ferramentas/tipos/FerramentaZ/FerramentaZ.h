#ifndef TP_FERRAMENTAZ_H
#define TP_FERRAMENTAZ_H
#include "../../Ferramenta.h"

class FerramentaZ : public Ferramenta {
public:
    // Construtor recebe coordenadas
    FerramentaZ(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "FerramentaZ"; }
    char getRepresentacao() const override { return 'z'; }
};

#endif //TP_FERRAMENTAZ_H