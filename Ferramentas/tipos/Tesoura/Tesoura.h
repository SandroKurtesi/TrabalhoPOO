//
// Created by pedro on 29/10/2025.
//

#ifndef TP_TESOURA_H
#define TP_TESOURA_H
#include "../../Ferramenta.h"


class Tesoura : public Ferramenta {
public:
    Tesoura();
    void usar(Solo& solo) override;
    std::string getTipo() const override { return "Tesoura"; }
    char getRepresentacao() const override { return 't'; }
};


#endif //TP_TESOURA_H