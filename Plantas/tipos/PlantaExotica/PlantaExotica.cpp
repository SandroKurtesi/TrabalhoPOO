#include "PlantaExotica.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;


PlantaExotica::PlantaExotica(int l, int c) : Planta(l, c) {

    this->agua = 50;
    this->nutrientes = 50;
    this->viva = true;
    this->idade = 0;
}


Planta* PlantaExotica::duplica(int l, int c)const {
    return new PlantaExotica(l, c);
}


void PlantaExotica::atualizar(Solo& solo) {

    if (solo.getAgua() > 0) {
        solo.setAgua(solo.getAgua() - 1);
        this->agua += 1;
    }


    int fome = 10;

    if (solo.getNutrientes() >= fome) {
        solo.setNutrientes(solo.getNutrientes() - fome);
        this->nutrientes += fome;
    }
    else {
        this->nutrientes -= 5;
        int oQueSobra = solo.getNutrientes();
        this->nutrientes += oQueSobra;
        solo.setNutrientes(0);
    }


    this->idade++;


    if (this->nutrientes <= 0 || this->idade > 100) {
        this->viva = false;
        solo.setNutrientes(solo.getNutrientes() + (this->nutrientes / 2));
    }
}


bool PlantaExotica::podemMultiplicar(const Solo& solo) const {
    return this->viva && this->nutrientes > 80;
}