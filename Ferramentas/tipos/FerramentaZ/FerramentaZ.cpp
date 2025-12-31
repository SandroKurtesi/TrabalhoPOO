#include "FerramentaZ.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;
int quantidade;

FerramentaZ::FerramentaZ(int l, int c) : Ferramenta(l, c) {

    quantidade = 3;
}

void FerramentaZ::usar(Solo &solo) {
    if (quantidade > 0) {

        solo.setAgua(50);
        solo.setNutrientes(50);

        quantidade--;

        cout << "ZAP! FerramentaZ usada. Solo equilibrado (50 A / 50 N). "
             << "Restam " << quantidade << " usos.\n";
    }
    else {
        cout << "A FerramentaZ esta sem energia (vazia)!\n";
    }
}