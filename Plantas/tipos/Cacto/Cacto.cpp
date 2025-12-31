#include "Cacto.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;

void Cacto::atualizar(Solo &solo) {

    int aguaNoSolo = solo.getAgua();

    int aguaParaBeber = aguaNoSolo * Settings::Cacto::absorcao_agua_percentagem / 100;

    solo.setAgua(aguaNoSolo - aguaParaBeber);
    this->agua += aguaParaBeber;


    int nutrNoSolo = solo.getNutrientes();
    int nutrParaComer = Settings::Cacto::absorcao_nutrientes; // 5

    if (nutrNoSolo >= nutrParaComer) {
        solo.setNutrientes(nutrNoSolo - nutrParaComer);
        this->nutrientes += nutrParaComer;
    } else {
        solo.setNutrientes(0);
        this->nutrientes += nutrNoSolo;
    }




    if (solo.getAgua() > Settings::Cacto::morre_agua_solo_maior) {
        this->instantesComSoloMolhado++;
    } else {
        this->instantesComSoloMolhado = 0;
    }


    if (solo.getNutrientes() < Settings::Cacto::morre_nutrientes_solo_menor) {
        this->instantesSemNutrientes++;
    } else {
        this->instantesSemNutrientes = 0;
    }


    if (this->instantesComSoloMolhado >= Settings::Cacto::morre_agua_solo_instantes ||
        this->instantesSemNutrientes > Settings::Cacto::morre_nutrientes_solo_instantes) {

        this->viva = false;

        solo.setNutrientes(solo.getNutrientes() + this->nutrientes);

    }
}

bool Cacto::podemMultiplicar(const Solo &solo) const {

    return this->viva &&
           this->nutrientes > Settings::Cacto::multiplica_nutrientes_maior &&
           this->agua > Settings::Cacto::multiplica_agua_maior;
}