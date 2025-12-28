
#include "Solo.h"
#include <cstdlib>
#include "../Settings.h"

using namespace std;

Solo::Solo() {
    agua = Settings::Jardim::agua_min + rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1);     // [80, 100]
    nutrientes = Settings::Jardim::nutrientes_min + rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1);
}

int Solo::getAgua() const { return agua; }
int Solo::getNutrientes() const { return nutrientes; }
void Solo::setAgua(int a) { agua = a; }
void Solo::setNutrientes(int n) { nutrientes = n; }

string Solo::getRepresentacao() const {
    return " ";
}
