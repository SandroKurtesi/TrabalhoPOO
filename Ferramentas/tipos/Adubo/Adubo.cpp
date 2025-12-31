#include "Adubo.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h" // Precisas disto para mexer no Solo
#include <iostream>

using namespace std;

// Construtor
Adubo::Adubo(int l, int c) : Ferramenta(l, c) {

    quantidade = Settings::Adubo::capacidade;
}


void Adubo::usar(Solo &solo) {

    if (quantidade > 0) {


        int dose = Settings::Adubo::dose;
        int nutrientesAtuais = solo.getNutrientes();

        solo.setNutrientes(nutrientesAtuais + dose);


        quantidade -= dose;


        cout << "Adubo aplicado! + " << dose << " nutrientes no solo. (Restam " << quantidade << ")\n";
    }
    else {
        cout << "O saco de adubo esta vazio!\n";
    }
}