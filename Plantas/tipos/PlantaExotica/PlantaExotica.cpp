#include "PlantaExotica.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;

// Construtor
PlantaExotica::PlantaExotica(int l, int c) : Planta(l, c) {
    // Nota: Como mudaste getRepresentacao para método,
    // já não precisas de definir 'this->representacao = ...' se a variável não existir.
    // Mas se a classe Planta tiver a variável 'representacao', podes manter:
    // this->representacao = 'P';

    this->agua = 50;
    this->nutrientes = 50;
    this->viva = true;
    this->idade = 0;
}

// CORREÇÃO 2: Removi o 'const' aqui também
Planta* PlantaExotica::duplica(int l, int c)const {
    return new PlantaExotica(l, c);
}

// A Logica de Vida (IGUAL AO QUE TINHAS)
void PlantaExotica::atualizar(Solo& solo) {
    // 1. BEBER
    if (solo.getAgua() > 0) {
        solo.setAgua(solo.getAgua() - 1);
        this->agua += 1;
    }

    // 2. COMER (VAMPIRA)
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

    // 3. ENVELHECER
    this->idade++;

    // 4. MORTE
    if (this->nutrientes <= 0 || this->idade > 100) {
        this->viva = false;
        solo.setNutrientes(solo.getNutrientes() + (this->nutrientes / 2));
    }
}

// Regra de Reprodução
bool PlantaExotica::podemMultiplicar(const Solo& solo) const {
    return this->viva && this->nutrientes > 80;
}