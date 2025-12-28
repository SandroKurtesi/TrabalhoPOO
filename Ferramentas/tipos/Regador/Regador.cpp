#include "Regador.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;

// Construtor
Regador::Regador(int l, int c) : Ferramenta(l, c) {
    // Capacidade definida no Settings.h (200) ou hardcoded
    capacidade = Settings::Regador::capacidade;
}

void Regador::usar(Solo &solo) {
    if (capacidade > 0) {
        // 1. Aumenta a água do solo (Dose = 10)
        int dose = Settings::Regador::dose;
        solo.setAgua(solo.getAgua() + dose);

        // 2. Gasta do regador
        capacidade -= dose;

        cout << "Regaste o solo! + " << dose << " agua. (Restam " << capacidade << ")\n";
    } else {
        cout << "O regador esta seco!\n";
    }
}