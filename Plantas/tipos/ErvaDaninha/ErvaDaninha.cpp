#include "ErvaDaninha.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;



void ErvaDaninha::atualizar(Solo &solo) {

    this->idade++;

    // Se a planta já se reproduziu alguma vez
    // incrementamos o contador para saber quando pode reproduzir de novo.
    this->ultimoMultiplicar++;


    // absorve 1 unidade de água do solo
    if (solo.getAgua() >= Settings::ErvaDaninha::absorcao_agua) {
        solo.setAgua(solo.getAgua() - Settings::ErvaDaninha::absorcao_agua);
        this->agua += Settings::ErvaDaninha::absorcao_agua;
    }

    // absorve 1 unidade de nutrientes do solo, se existir
    if (solo.getNutrientes() >= Settings::ErvaDaninha::absorcao_nutrientes) {
        solo.setNutrientes(solo.getNutrientes() - Settings::ErvaDaninha::absorcao_nutrientes);
        this->nutrientes += Settings::ErvaDaninha::absorcao_nutrientes;
    }


    // Morre sozinha passados 60 tempos"
    if (this->idade >= Settings::ErvaDaninha::morre_instantes) {
        this->viva = false;
    }
}

bool ErvaDaninha::podemMultiplicar(const Solo &solo) const {
    // Nutrientes > 30 E passaram 5 instantes desde a última vez
    bool condicaoNutrientes = this->nutrientes > Settings::ErvaDaninha::multiplica_nutrientes_maior; // > 30
    bool condicaoTempo = this->ultimoMultiplicar >= Settings::ErvaDaninha::multiplica_instantes; // >= 5

    return this->viva && condicaoNutrientes && condicaoTempo;
}