#include "Roseira.h"

#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;

void Roseira::atualizar(Solo &solo) {


    if (this->agua >= Settings::Roseira::perda_agua)
        this->agua -= Settings::Roseira::perda_agua;
    else
        this->agua = 0;

    if (this->nutrientes >= Settings::Roseira::perda_nutrientes)
        this->nutrientes -= Settings::Roseira::perda_nutrientes;
    else
        this->nutrientes = 0;



    int aguaNoSolo = solo.getAgua();
    int aguaParaBeber = Settings::Roseira::absorcao_agua; // 5

    if (aguaNoSolo >= aguaParaBeber) {

        solo.setAgua(aguaNoSolo - aguaParaBeber);
        this->agua += aguaParaBeber;
    } else {

        solo.setAgua(0);
        this->agua += aguaNoSolo;
    }



    int nutrNoSolo = solo.getNutrientes();
    int nutrParaComer = Settings::Roseira::absorcao_nutrientes;

    if (nutrNoSolo >= nutrParaComer) {
        solo.setNutrientes(nutrNoSolo - nutrParaComer);
        this->nutrientes += nutrParaComer;
    } else {
        solo.setNutrientes(0);
        this->nutrientes += nutrNoSolo;
    }



    if (this->agua < Settings::Roseira::morre_agua_menor ||
        this->nutrientes < Settings::Roseira::morre_nutrientes_menor ||
        this->nutrientes > Settings::Roseira::morre_nutrientes_maior)
    {
        this->viva = false;

        solo.setNutrientes(solo.getNutrientes() + (this->nutrientes / 2));
        solo.setAgua(solo.getAgua() + (this->agua / 2));
    }
}

bool Roseira::podemMultiplicar(const Solo &solo) const {


    return this->viva && (this->nutrientes > Settings::Roseira::multiplica_nutrientes_maior);
}