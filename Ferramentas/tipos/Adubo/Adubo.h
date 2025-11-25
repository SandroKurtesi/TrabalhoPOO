#ifndef TP_ADUBO_H
#define TP_ADUBO_H
#include "../../Ferramenta.h"

class Adubo : public Ferramenta {
    int quantidade = 100;

public:
    // Construtor recebe coordenadas
    Adubo(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Adubo"; }
    char getRepresentacao() const override { return 'a'; }
};

#endif //TP_ADUBO_H