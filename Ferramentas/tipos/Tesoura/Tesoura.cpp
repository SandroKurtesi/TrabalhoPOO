
#include "Tesoura.h"
using namespace std;
#include <iostream>

Tesoura::Tesoura(int l, int c) : Ferramenta(l, c) {
}

void Tesoura::usar(Solo &solo) {
    // eliminar plantas feias
}

bool Tesoura::tentarCortar(Planta* p) {
    if (p == nullptr) return false;

    // A Tesoura decide: "Eu odeio Ervas Daninhas!"
    if (p->getTipo() == "ErvaDaninha") {

        // Podemos meter o cout aqui para ficar encapsulado
        cout << "ZAS! A Tesoura cortou a planta " << p->getTipo() << "!\n";

        return true; // Sim, cortei!
    }

    // Se for Roseira, Cacto, etc.
    // cout << "A tesoura recusa-se a cortar a bela " << p->getTipo() << ".\n";
    return false; // Não cortei.
}