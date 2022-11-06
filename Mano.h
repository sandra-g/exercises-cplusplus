#pragma once
#ifndef MANO_H
#define MANO_H
#include <fstream>//files
#include <vector>//vector
using namespace std;

class Mano {
private:
    struct Carta {
        int val;
        char tipo;
    };
    Carta cartas[5];//siempre seran 5 cartas
    string cartasString;
    int clase = -1;//por defecto
    int valorMejor = -1;//por defecto
    vector<int> mejores;//guardare los valores de las cartas del mejor al menor
public:
    Mano();//por defecto
    ~Mano();//por defecto
    void leerMano(ifstream&);
    void obtenerMejorClase();
    int getClase();//me da la mejor clase que tiene la mano
    int getValorMejor();
    vector<int> getMejores();//devuelve los valores ordenados por su importancia
    string getCartasString();
};

#endif /* MANO_H */