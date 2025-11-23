

#ifndef TP_ADUBO_H
#define TP_ADUBO_H
#include "../../Ferramenta.h"
#include "../../../Settings.h"


class Adubo : public Ferramenta {
    int quantidade = 100;

public:
    Adubo();
    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Adubo"; }
    char getRepresentacao() const override { return 'a'; }

};


#endif //TP_ADUBO_H