

#include "Ferramenta.h"

int Ferramenta::contador = 0;

Ferramenta::Ferramenta() {
    id = ++contador;
}
