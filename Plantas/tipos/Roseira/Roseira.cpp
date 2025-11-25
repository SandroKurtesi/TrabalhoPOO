#include "Roseira.h"

#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;

void Roseira::atualizar(Solo &solo) {

    // O enunciado diz: "perde 4 unidades de água e 4 de nutrientes"
    this->agua -= Settings::Roseira::perda_agua;
    this->nutrientes -= Settings::Roseira::perda_nutrientes;


    // O enunciado diz: "absorve 5 unidades de água do solo (se existir)"
    int aguaNoSolo = solo.getAgua();
    int aguaParaBeber = Settings::Roseira::absorcao_agua; // 5

    if (aguaNoSolo >= aguaParaBeber) {
        // Há água suficiente
        solo.setAgua(aguaNoSolo - aguaParaBeber);
        this->agua += aguaParaBeber;
    } else {
        // Não há suficiente, bebe tudo o que houver
        solo.setAgua(0);
        this->agua += aguaNoSolo;
    }


    // O enunciado diz: "absorve 8 unidades de nutrientes"
    int nutrNoSolo = solo.getNutrientes();
    int nutrParaComer = Settings::Roseira::absorcao_nutrientes; // 8

    if (nutrNoSolo >= nutrParaComer) {
        solo.setNutrientes(nutrNoSolo - nutrParaComer);
        this->nutrientes += nutrParaComer;
    } else {
        solo.setNutrientes(0);
        this->nutrientes += nutrNoSolo;
    }


    // Morre se: agua == 0, nutr == 0, ou nutr > 199
    if (this->agua <= Settings::Roseira::morre_agua_menor ||
        this->nutrientes <= Settings::Roseira::morre_nutrientes_menor ||
        this->nutrientes >= 200) // Valor fixo ou usa Settings se tiveres criado constante
    {
        this->viva = false;

        // Regra: "Ao morrer deixa no solo metade dos nutrientes... e metade da água"
        solo.setNutrientes(solo.getNutrientes() + (this->nutrientes / 2));
        solo.setAgua(solo.getAgua() + (this->agua / 2));
    }
}

bool Roseira::podemMultiplicar(const Solo &solo) const {
    // Regra: Multiplica-se se "quantidade acumulada de nutrientes for maior do que 100"

    return this->viva && (this->nutrientes > Settings::Roseira::multiplica_nutrientes_maior);
}