#include "Regador.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;


Regador::Regador(int l, int c) : Ferramenta(l, c) {

    capacidade = Settings::Regador::capacidade;
}

void Regador::usar(Solo &solo) {
    if (capacidade > 0) {

        int dose = Settings::Regador::dose;
        solo.setAgua(solo.getAgua() + dose);


        capacidade -= dose;

        cout << "Regaste o solo! + " << dose << " agua. (Restam " << capacidade << ")\n";
    } else {
        cout << "O regador esta seco!\n";
    }
}