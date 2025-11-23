
#ifndef TP_SOLO_H
#define TP_SOLO_H

#include <string>

class Solo {
    int agua;
    int nutrientes;

public:
    Solo();
    int getAgua() const;
    int getNutrientes() const;
    void setAgua(int a);
    void setNutrientes(int n);
    std::string getRepresentacao() const;
};

#endif //TP_SOLO_H
