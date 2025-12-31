#ifndef TP_FERRAMENTA_H
#define TP_FERRAMENTA_H
#include <string>

class Solo;

class Ferramenta {
protected:
    static int contador;
    int id;
    bool ativa = false;


    int linha = -1;
    int coluna = -1;

public:

    Ferramenta(int l = -1, int c = -1);

    virtual ~Ferramenta() = default;


    int getId() const { return id; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }


    void setPosicao(int l, int c) { linha = l; coluna = c; }
    void setId(int i) { id = i; }

    bool estaAtiva() const { return ativa; }
    void setAtiva(bool estado) { ativa = estado; }

    virtual void usar(Solo& solo) = 0;
    virtual std::string getTipo() const = 0;
    virtual char getRepresentacao() const = 0;
};

#endif //TP_FERRAMENTA_H