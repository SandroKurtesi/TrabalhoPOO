

#ifndef TP_ROSEIRA_H
#define TP_ROSEIRA_H
#include "../../Planta.h"
#include "../../../Settings.h"


class Roseira :public Planta {
public:
    Roseira(int l, int c)
            : Planta(l, c, Settings::Roseira::inicial_agua, Settings::Roseira::inicial_nutrientes, Beleza::BONITA)
    {}

    void atualizar(Solo& solo) override;
    bool podemMultiplicar(const Solo &solo) const override;

    char getRepresentacao() const override { return 'r'; }
    std::string getTipo() const override { return "Roseira"; }
};


#endif //TP_ROSEIRA_H