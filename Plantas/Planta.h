

#ifndef TP_PLANTA_H
#define TP_PLANTA_H
#include <string>
#include <sstream>

class Solo;

class Planta {
public:
    enum class Beleza { FEIA, BONITA, NEUTRA };
protected:
    int linha;
    int coluna;

    int agua;
    int nutrientes;
    bool viva = true;
    Beleza beleza;

    int idade;

public:
    Planta(int l,int c,int a = 0, int n = 0, Beleza b = Beleza::NEUTRA)
        : linha(l),coluna(c), agua(a), nutrientes(n), beleza(b) {}

    virtual ~Planta() = default;

    virtual void atualizar(Solo& solo) = 0;
    virtual bool podemMultiplicar(const Solo& solo) const = 0;
    virtual char getRepresentacao() const = 0;
    virtual std::string getTipo() const = 0;

    virtual void posReproducao() {}



    bool estaViva() const { return viva; }
    int getAgua() const { return agua; }
    int getNutrientes() const { return nutrientes; }

    int getLinha() const { return linha; }
    int getColuna() const { return coluna; }
    Beleza getBeleza() const { return beleza; }

    std::string belezaToString() const {
        switch (beleza) {
            case Beleza::FEIA:   return "Feia";
            case Beleza::BONITA: return "Bonita";
                default:         return "Neutra";
        }
    }

    virtual std::string getDescricao() const {
        std::ostringstream oss;
        oss << getTipo() << " (" << getRepresentacao() << ") "
            << "| Pos: " << (char)('A' + linha) << (char)('A' + coluna)
            << " | Agua: " << agua
            << " | Nutr: " << nutrientes
            << " | Saude: " << (viva ? "Viva" : "Morta");
        return oss.str();
    }


    int getIdade() const { return idade; }


    void setIdade(int i) { idade = i; }


    void setAgua(int a) { agua = a; }
    void setNutrientes(int n) { nutrientes = n; }

};


#endif //TP_PLANTA_H