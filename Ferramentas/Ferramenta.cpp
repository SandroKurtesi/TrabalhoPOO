#include "Ferramenta.h"

int Ferramenta::contador = 0;

Ferramenta::Ferramenta(int l, int c) : linha(l), coluna(c) {
    id = ++contador;
}