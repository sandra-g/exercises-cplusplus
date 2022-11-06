#include "Mano.h"
#include <iostream>//cout
#include <iomanip>//setw
#include <map>//map
#include <cctype>//isdigit()
#include <string>
using namespace std;

Mano::Mano() {

}
Mano::~Mano() {

}
void Mano::leerMano(ifstream& arch) {
    char val;
    char tipo;
    cartasString = "";//reseteo el string donde guardo las cartas leidas para imprimir
    for (int i = 0; i < 5; i++) {
        Carta carta;
        arch >> val >> tipo;
        if (arch.eof()) break;
        cartasString += val;
        cartasString += tipo;
        cartasString += " ";
        if (isdigit(val))
            carta.val = val - '0';
        else {
            if (val == 'T')
                carta.val = 10;
            if (val == 'J')
                carta.val = 11;
            if (val == 'Q')
                carta.val = 12;
            if (val == 'K')
                carta.val = 13;
            if (val == 'A')
                carta.val = 14;
        }
        carta.tipo = tipo;
        cartas[i] = carta;
    }
    mejores.clear();//limpio el vector para los nuevos mejores
}

void Mano::obtenerMejorClase() {
    map<int, int> mapaNumeros;//que numeros tengo
    map<char, int> mapaTipos;//que numeros tengo
    for (Carta c : cartas) {
        mapaNumeros[c.val]++;
        mapaTipos[c.tipo]++;
    }

    if (mapaTipos.size() == 1) {//solo existe 1 clase de cartas: posibles: Royal flush, straight flush, flush 
        if (mapaNumeros.count(10) && mapaNumeros.count(11) && mapaNumeros.count(12) && mapaNumeros.count(13) && mapaNumeros.count(14)) {//Royal flush
            clase = 10;//Royal flush
            valorMejor = 14;
            mejores.push_back(14);
            mejores.push_back(13);
            mejores.push_back(12);
            mejores.push_back(11);
            mejores.push_back(10);
            return;
        }
    }
    if (mapaTipos.size() == 1) {//solo existe 1 clase de cartas: posibles: straight flush, flush 
        if (mapaNumeros.size() == 5) {//todos diferentes: posible straight flush
            bool resp = true;
            map<int, int>::reverse_iterator it1 = mapaNumeros.rbegin();
            map<int, int>::reverse_iterator it2 = it1;
            it2++;
            while (it2 != mapaNumeros.rend()) {
                if (it1->first - it2->first != 1)
                    resp = false;
                it1++;
                it2++;
            }
            if (resp) {
                clase = 9;
                valorMejor = mapaNumeros.rbegin()->first;
                for (it1 = mapaNumeros.rbegin(); it1 != mapaNumeros.rend();/**/) {
                    mejores.push_back(it1->first);
                    it1->second--;
                    if (it1->second == 0)
                        it1++;
                }
                return;
            }
        }
    }

    if (mapaNumeros.size() == 2) {//existen 2 clases diferentes de cartas: posible: four of a kind
        int cant1;
        int cant2;
        cant1 = mapaNumeros.begin()->second;
        cant2 = mapaNumeros.rbegin()->second;
        if ((cant1 == 4 && cant2 == 1) || (cant1 == 1 && cant2 == 4)) {
            clase = 8;//Four of a kind
            if (cant1 == 4) {
                valorMejor = mapaNumeros.begin()->first;
                mejores.push_back(mapaNumeros.begin()->first);
                mejores.push_back(mapaNumeros.rbegin()->first);
            }
            else {
                valorMejor = mapaNumeros.rbegin()->first;
                mejores.push_back(mapaNumeros.rbegin()->first);
                mejores.push_back(mapaNumeros.begin()->first);
            }
            return;
        }
    }

    if (mapaNumeros.size() == 2) {//existen 2 valores diferentes. posible: full house
        int cant1;
        int cant2;
        cant1 = mapaNumeros.begin()->second;
        cant2 = mapaNumeros.rbegin()->second;
        if ((cant1 == 3 && cant2 == 2) || (cant1 == 2 && cant2 == 3)) {
            clase = 7;//Full house
            if (cant1 == 3) {
                valorMejor = mapaNumeros.begin()->first;
                mejores.push_back(mapaNumeros.begin()->first);
                mejores.push_back(mapaNumeros.rbegin()->first);
            }
            else {
                valorMejor = mapaNumeros.rbegin()->first;
                mejores.push_back(mapaNumeros.rbegin()->first);
                mejores.push_back(mapaNumeros.begin()->first);
            }
            return;
        }
    }

    if (mapaTipos.size() == 1) {//todos mismo tipo. ya estaban descartados royal flush y straight flush. posible: flush
        clase = 6;//Flush
        valorMejor = mapaNumeros.rbegin()->first;
        for (map<int, int>::reverse_iterator it1 = mapaNumeros.rbegin(); it1 != mapaNumeros.rend();) {
            mejores.push_back(it1->first);
            it1->second--;
            if (it1->second == 0)
                it1++;
        }
        return;
    }

    if (mapaNumeros.size() == 5) {//todos valores diferentes. posible: Straight(consecutivos) o High card(no consecutivos)
        map<int, int>::reverse_iterator it = mapaNumeros.rbegin();
        int val = it->first;
        it++;//incremento, voy a comparar abajo
        bool resp = true;
        while (it != mapaNumeros.rend()) {
            if (val - it->first != 1)
                resp = false;
            val = it->first;
            it++;
        }
        if (resp) {
            clase = 5;//Straight
            valorMejor = mapaNumeros.rbegin()->first;
            for (it = mapaNumeros.rbegin(); it != mapaNumeros.rend(); it++)
                mejores.push_back(it->first);
            return;
        }
    }

    if (mapaNumeros.size() == 3) {//three of a kind: 3 del mismo valor, pero los demas no son par ni nada
        int cant1, val1;
        int cant2, val2;
        int cant3, val3;
        map<int, int>::iterator it = mapaNumeros.begin();
        cant1 = it->second;
        val1 = it->first;
        it++;
        cant2 = it->second;
        val2 = it->first;
        it++;
        cant3 = it->second;
        val3 = it->first;
        if (cant1 == 3 || cant2 == 3 || cant3 == 3) {
            clase = 4;//three of a kind
            map<int, int>::reverse_iterator itR;
            if (cant1 == 3) {
                valorMejor = val1;
                mejores.push_back(val1);
                for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); itR++)
                    if (itR->first != val1)
                        mejores.push_back(itR->first);
            }
            if (cant2 == 3) {
                valorMejor = val2;
                mejores.push_back(cant2);
                for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); itR++)
                    if (itR->first != val2)
                        mejores.push_back(itR->first);
            }
            if (cant3 == 3) {
                valorMejor = val3;
                mejores.push_back(cant3);
                for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); itR++)
                    if (itR->first != val3)
                        mejores.push_back(itR->first);
            }
            return;
        }//aca se cogera el mejorval..y sino entonces los otros 2 que no son ese
    }

    if (mapaNumeros.size() == 3) {//dos pares diferentes y una carta suelta
        int cant1, val1;
        int cant2, val2;
        int cant3, val3;
        map<int, int>::iterator it = mapaNumeros.begin();
        cant1 = it->second;
        val1 = it->first;
        it++;
        cant2 = it->second;
        val2 = it->first;
        it++;
        cant3 = it->second;
        val3 = it->first;
        if ((cant1 == 2 && cant2 == 2) || (cant2 == 2 && cant3 == 2) || (cant1 == 2 && cant3 == 2)) {
            clase = 3;//two pairs diferentes y uno suelto
            int aux;
            map<int, int>::reverse_iterator itR;
            for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); itR++)
                if (itR->second == 2)
                    mejores.push_back(itR->first);
                else aux = itR->first;
            mejores.push_back(aux);
            valorMejor = mejores[0];
            return;
        }
    }

    if (mapaNumeros.size() == 4) {//un par y el resto diferentes
        int cant1, val1;
        int cant2, val2;
        int cant3, val3;
        int cant4, val4;
        map<int, int>::iterator it = mapaNumeros.begin();
        cant1 = it->second;
        val1 = it->first;
        it++;
        cant2 = it->second;
        val2 = it->first;
        it++;
        cant3 = it->second;
        val3 = it->first;
        it++;
        cant4 = it->second;
        val4 = it->first;
        if (cant1 == 2 || cant2 == 2 || cant3 == 2 || cant4 == 2) {
            clase = 2;//One pair
            map<int, int>::reverse_iterator itR;
            for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); itR++)
                if (itR->second == 2)
                    mejores.push_back(itR->first);
            for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); itR++)
                if (itR->second != 2)
                    mejores.push_back(itR->first);
            valorMejor = mejores[0];
            return;
        }
    }

    if (mapaNumeros.size() == 5) {//todos diferentes sin orden ni nada
        clase = 1;//High card
        valorMejor = mapaNumeros.rbegin()->first;// mapaNumeros.rend()->first;
        map<int, int>::reverse_iterator itR;
        for (itR = mapaNumeros.rbegin(); itR != mapaNumeros.rend(); /*itR++*/) {
            mejores.push_back(itR->first);
            itR->second--;
            if (itR->second == 0)
                itR++;
        }
        return;
    }
}

int Mano::getClase() {
    return clase;
}

int Mano::getValorMejor() {
    return valorMejor;
}

vector<int> Mano::getMejores() {
    return mejores;
}

string Mano::getCartasString() {
    return cartasString;
}