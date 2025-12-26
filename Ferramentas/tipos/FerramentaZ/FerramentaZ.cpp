#include "FerramentaZ.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;
int quantidade;

FerramentaZ::FerramentaZ(int l, int c) : Ferramenta(l, c) {
    // Começa com 3 cargas (ou usa um valor do Settings se preferires)
    quantidade = 3;
}

void FerramentaZ::usar(Solo &solo) {
    if (quantidade > 0) {
        // A Magia: Restaura o equilíbrio do solo
        solo.setAgua(50);
        solo.setNutrientes(50);

        quantidade--; // Gasta 1 uso

        cout << "ZAP! FerramentaZ usada. Solo equilibrado (50 A / 50 N). "
             << "Restam " << quantidade << " usos.\n";
    }
    else {
        cout << "A FerramentaZ esta sem energia (vazia)!\n";
    }
}