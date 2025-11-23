
#include "Solo.h"
#include <cstdlib>

using namespace std;

Solo::Solo() {
    agua = 80 + rand() % 21;        // [80, 100]
    nutrientes = 40 + rand() % 11;   // [40, 50]
}

int Solo::getAgua() const { return agua; }
int Solo::getNutrientes() const { return nutrientes; }
void Solo::setAgua(int a) { agua = a; }
void Solo::setNutrientes(int n) { nutrientes = n; }

string Solo::getRepresentacao() const {
    return " ";
}
