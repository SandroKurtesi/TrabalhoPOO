

#ifndef TP_FERRAMENTAZ_H
#define TP_FERRAMENTAZ_H
#include "../../Ferramenta.h"


class FerramentaZ : public Ferramenta {
public:
    FerramentaZ();
    void usar(Solo& solo) override;
    std::string getTipo() const override { return "FerramentaZ"; }
    char getRepresentacao() const override { return 'z'; }
};


#endif //TP_FERRAMENTAZ_H