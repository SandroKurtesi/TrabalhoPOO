

#ifndef TP_SIMULADOR_H
#define TP_SIMULADOR_H

#include "../Jardim/Jardim.h"
#include <string>

class Simulador {
    Jardim* jardim = nullptr;
    bool ativo = true;

public:
    ~Simulador();
    void iniciar();
    void processarComando(const std::string& linha);
};

#endif //TP_SIMULADOR_H
