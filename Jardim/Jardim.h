

#ifndef TP_JARDIM_H
#define TP_JARDIM_H

#include "../Solo/Solo.h"
#include "../Jardineiro/Jardineiro.h"
#include <iostream>
#include <vector>

#include "../Plantas/Planta.h"
#include "../Ferramentas/Ferramenta.h"

class Jardim {
    int linhas;
    int colunas;
    Solo** grelha;
    Jardineiro jardineiro;

    std::vector<Planta*> plantas;
    std::vector<Ferramenta*> ferramentas;

    bool getVizinhaLivre(int l, int c, int& resL, int& resC);

    void spawnFerramentaAleatoria();

public:
    Jardim(int l, int c);
    ~Jardim();

    static bool dimensoesValidas(int l, int c);

    void verificarFerramentasNoChao();

    bool adicionarPlanta(const std::string& tipo, int l, int c);


    void mostrar() const;
    void infoSolo(int l, int c) const;
    Jardineiro& getJardineiro();
    int getLinhas() const;
    int getColunas() const;


    bool colherPlanta(int l, int c);
    void mostrarSolo(int l,int c,int raio);

    void avancaInstante();

    void removerPlanta(int l, int c);

    void listarTodasPlantas() const;      // Para lplantas
    void listarPlanta(int l, int c) const; // Para lplanta
    void listarArea() const;

    bool carregarEstado(const std::string& estado);
    std::string getEstadoComoString() const;

    int contarVizinhosOcupados(int l, int c);




};

#endif //TP_JARDIM_H
