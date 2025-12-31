#ifndef TP_ADUBO_H
#define TP_ADUBO_H
#include "../../Ferramenta.h"
#include "../../../Settings.h"

class Adubo : public Ferramenta {
    int quantidade = Settings::Adubo::capacidade;

public:

    Adubo(int l = -1, int c = -1);

    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Adubo"; }
    char getRepresentacao() const override { return 'a'; }

    int getQuantidade() const { return quantidade; }
};

#endif //TP_ADUBO_H