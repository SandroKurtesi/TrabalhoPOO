

#ifndef TP_FERRAMENTA_H
#define TP_FERRAMENTA_H
#include <string>

class Solo;

class Ferramenta {
protected:
    static int contador;
    int id;
    bool ativa = false; // se está na mão do jardineiro

public:
    Ferramenta();
    virtual ~Ferramenta() = default;

    int getId() const { return id; }
    bool estaAtiva() const { return ativa; }
    void setAtiva(bool estado) { ativa = estado; }

    virtual void usar(Solo& solo) = 0;
    virtual std::string getTipo() const = 0;
    virtual char getRepresentacao() const = 0;
};


#endif //TP_FERRAMENTA_H