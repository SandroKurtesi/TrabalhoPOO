#ifndef TP_REGADOR_H
#define TP_REGADOR_H
#include "../../Ferramenta.h"

class Regador : public Ferramenta {
    int capacidade = 200;

public:
    // Construtor recebe coordenadas
    Regador(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Regador"; }
    char getRepresentacao() const override { return 'g'; }
};

#endif //TP_REGADOR_H