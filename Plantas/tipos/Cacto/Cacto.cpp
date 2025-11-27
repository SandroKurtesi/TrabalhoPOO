#include "Cacto.h"
#include "../../../Settings.h"
#include "../../../Solo/Solo.h"
#include <iostream>

using namespace std;

void Cacto::atualizar(Solo &solo) {
    // 1. ABSORÇÃO (Água: 25%, Nutrientes: 5)

    // Água (Percentagem)
    int aguaNoSolo = solo.getAgua();
    // (usar float para precisão ou int direto)
    int aguaParaBeber = aguaNoSolo * Settings::Cacto::absorcao_agua_percentagem / 100;

    solo.setAgua(aguaNoSolo - aguaParaBeber);
    this->agua += aguaParaBeber;

    // Nutrientes (Fixo)
    int nutrNoSolo = solo.getNutrientes();
    int nutrParaComer = Settings::Cacto::absorcao_nutrientes; // 5

    if (nutrNoSolo >= nutrParaComer) {
        solo.setNutrientes(nutrNoSolo - nutrParaComer);
        this->nutrientes += nutrParaComer;
    } else {
        solo.setNutrientes(0);
        this->nutrientes += nutrNoSolo;
    }

    // 2. REGRAS DE MORTE (Contadores de Dias Seguidos)

    // Regra A: Excesso de Água (> 100)
    // Atenção: Verifica a água que ESTÁ no solo agora (depois de beber)
    if (solo.getAgua() > Settings::Cacto::morre_agua_solo_maior) {
        this->instantesComSoloMolhado++;
    } else {
        this->instantesComSoloMolhado = 0; // Reset se o solo secar
    }

    // Regra B: Falta de Nutrientes (0)
    if (solo.getNutrientes() <= Settings::Cacto::morre_nutrientes_solo_menor) {
        this->instantesSemNutrientes++;
    } else {
        this->instantesSemNutrientes = 0; // Reset se houver comida
    }

    // 3. MORTE EFETIVA
    if (this->instantesComSoloMolhado >= Settings::Cacto::morre_agua_solo_instantes ||
        this->instantesSemNutrientes >= Settings::Cacto::morre_nutrientes_solo_instantes) {

        this->viva = false;

        // "Ao morrer deixa no solo todos os nutrientes que absorveu"
        // (Assume-se que devolve o que tem no corpo)
        solo.setNutrientes(solo.getNutrientes() + this->nutrientes);
        // A água não é devolvida segundo a regra do Cacto.
    }
}

bool Cacto::podemMultiplicar(const Solo &solo) const {
    // Regra: Nutrientes > 100 E Agua > 50
    return this->viva &&
           this->nutrientes > Settings::Cacto::multiplica_nutrientes_maior &&
           this->agua > Settings::Cacto::multiplica_agua_maior;
}