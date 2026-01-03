
#include "Tesoura.h"
using namespace std;
#include <iostream>

Tesoura::Tesoura(int l, int c) : Ferramenta(l, c) {
}

void Tesoura::usar(Solo &solo) {

}

bool Tesoura::tentarCortar(Planta* p) {
    if (p == nullptr) return false;

    if (p->getTipo() == "ErvaDaninha") {

        cout << "A Tesoura cortou a planta " << p->getTipo() << "!\n";

        return true;
    }

    return false;
}