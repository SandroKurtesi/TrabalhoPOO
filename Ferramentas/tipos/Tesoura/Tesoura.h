#ifndef TP_TESOURA_H
#define TP_TESOURA_H
#include "../../Ferramenta.h"
#include "../../../Plantas/Planta.h"

class Tesoura : public Ferramenta {
public:

    Tesoura(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Tesoura"; }
    char getRepresentacao() const override { return 't'; }
    bool tentarCortar(Planta* p);
};

#endif //TP_TESOURA_H