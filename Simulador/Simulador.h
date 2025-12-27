

#ifndef TP_SIMULADOR_H
#define TP_SIMULADOR_H

#include "../Jardim/Jardim.h"
#include <string>
#include <map>

class Simulador {
    Jardim* jardim = nullptr;
    bool ativo = true;
    std::map<std::string, std::string> copias;



public:
    ~Simulador();
    void iniciar();
    void processarComando(const std::string& linha);
};

#endif //TP_SIMULADOR_H
