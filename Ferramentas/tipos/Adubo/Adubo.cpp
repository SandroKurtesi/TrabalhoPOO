#include "Adubo.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h" // Precisas disto para mexer no Solo
#include <iostream>

using namespace std;

// Construtor
Adubo::Adubo(int l, int c) : Ferramenta(l, c) {
    // Inicializa a quantidade com o valor das definições (normalmente 100)
    quantidade = Settings::Adubo::capacidade;
}

// Ação de usar
void Adubo::usar(Solo &solo) {
    // 1. Verifica se o saco ainda tem adubo
    if (quantidade > 0) {

        // 2. Aumenta os nutrientes do solo
        int dose = Settings::Adubo::dose; // Normalmente 10
        int nutrientesAtuais = solo.getNutrientes();

        solo.setNutrientes(nutrientesAtuais + dose);

        // 3. Gasta do saco
        quantidade -= dose;

        // Feedback visual para saberes que funcionou
        cout << "Adubo aplicado! + " << dose << " nutrientes no solo. (Restam " << quantidade << ")\n";
    }
    else {
        cout << "O saco de adubo esta vazio!\n";
    }
}