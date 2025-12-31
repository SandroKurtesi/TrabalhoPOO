#ifndef FERRAMENTAZ_H
#define FERRAMENTAZ_H

#include "../../Ferramenta.h"
#include <string>

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ(int l=-1, int c=-1);


    void usar(Solo &solo) override;


    char getRepresentacao() const override { return 'Z'; }


    std::string getTipo() const override { return "FerramentaZ"; }
};

#endif // FERRAMENTAZ_H