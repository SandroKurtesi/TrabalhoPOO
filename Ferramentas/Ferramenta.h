#ifndef TP_FERRAMENTA_H
#define TP_FERRAMENTA_H
#include <string>

class Solo;

class Ferramenta {
protected:
    static int contador;
    int id;
    bool ativa = false; // se está na mão do jardineiro

    // --- NOVOS: Coordenadas ---
    int linha = -1;
    int coluna = -1;

public:
    // Construtor atualizado
    Ferramenta(int l = -1, int c = -1); // Default para -1 (inventário)

    virtual ~Ferramenta() = default;

    // Getters
    int getId() const { return id; }
    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }

    // Setters (importante para quando apanhas/largas)
    void setPosicao(int l, int c) { linha = l; coluna = c; }

    bool estaAtiva() const { return ativa; }
    void setAtiva(bool estado) { ativa = estado; }

    virtual void usar(Solo& solo) = 0;
    virtual std::string getTipo() const = 0;
    virtual char getRepresentacao() const = 0;
};

#endif //TP_FERRAMENTA_H