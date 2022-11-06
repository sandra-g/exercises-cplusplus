#pragma once
#ifndef JUEGO_H
#define JUEGO_H
#include <string>
using namespace std;
#include "Mano.h"
class Juego {
private:
    Mano mano1;
    Mano mano2;
public:
    void jugar(string);
    int comparar(Mano, Mano);
    int desempatar(Mano, Mano,int&,int&);//si la clase y valor son iguales, voy a comparar el resto de cartas
    void resultados(Mano, Mano, int&, ofstream&);
};

#endif /* JUEGO_H */