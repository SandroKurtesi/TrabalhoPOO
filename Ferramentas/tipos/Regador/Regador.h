#ifndef TP_REGADOR_H
#define TP_REGADOR_H
#include "../../Ferramenta.h"
#include "../../../Settings.h"

class Regador : public Ferramenta {
    int capacidade = Settings::Regador::capacidade;

public:

    Regador(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Regador"; }
    char getRepresentacao() const override { return 'g'; }

    int getAgua() const { return capacidade; }
};

#endif //TP_REGADOR_H