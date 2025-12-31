#include "ErvaDaninha.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;



void ErvaDaninha::atualizar(Solo &solo) {

    this->idade++;


    this->ultimoMultiplicar++;



    if (solo.getAgua() >= Settings::ErvaDaninha::absorcao_agua) {
        solo.setAgua(solo.getAgua() - Settings::ErvaDaninha::absorcao_agua);
        this->agua += Settings::ErvaDaninha::absorcao_agua;
    }


    if (solo.getNutrientes() >= Settings::ErvaDaninha::absorcao_nutrientes) {
        solo.setNutrientes(solo.getNutrientes() - Settings::ErvaDaninha::absorcao_nutrientes);
        this->nutrientes += Settings::ErvaDaninha::absorcao_nutrientes;
    }



    if (this->idade >= Settings::ErvaDaninha::morre_instantes) {
        this->viva = false;
    }
}

bool ErvaDaninha::podemMultiplicar(const Solo &solo) const {

    bool condicaoNutrientes = this->nutrientes > Settings::ErvaDaninha::multiplica_nutrientes_maior;
    bool condicaoTempo = this->ultimoMultiplicar >= Settings::ErvaDaninha::multiplica_instantes;

    return this->viva && condicaoNutrientes && condicaoTempo;
}