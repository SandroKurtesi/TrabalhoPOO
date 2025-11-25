#ifndef TP_TESOURA_H
#define TP_TESOURA_H
#include "../../Ferramenta.h"

class Tesoura : public Ferramenta {
public:
    // Construtor recebe coordenadas
    Tesoura(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Tesoura"; }
    char getRepresentacao() const override { return 't'; }
};

#endif //TP_TESOURA_H