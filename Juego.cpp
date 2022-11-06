#include <fstream>//files
#include <iostream>//cout
#include <iomanip>
#include <vector>//vector
using namespace std;

#include "Mano.h"
#include "Juego.h"


int Juego::desempatar(Mano mano1, Mano mano2, int& desempate1, int& desempate2) {
    if (mano1.getClase() != mano2.getClase())
        return -1;

    if (mano1.getClase() == 10) {
        //no deberia ser posible un empate si ambos son ROYAL FLUSH. siempre hay ganador obvio.
    }

        vector<int> v1 = mano1.getMejores();
        vector<int> v2 = mano2.getMejores();
        vector<int>::iterator itR1 = v1.begin();
        vector<int>::iterator itR2 = v2.begin();
        itR1 = v1.begin();
        itR2 = v2.begin();
        while (itR1 != v1.end()) {
            if (*itR1 > *itR2) {
                desempate1 = *itR1;
                desempate2 = *itR2;
                return 1;
            }
            if (*itR1 < *itR2) {
                desempate1 = *itR1;
                desempate2 = *itR2;
                return 2;
            }
            itR1++;
            itR2++;
        }
        return -1;
    

    return -1;
}

int Juego::comparar(Mano mano1, Mano mano2) {
    if (mano1.getClase() == -1 || mano2.getClase() == -1)//por alguna razon nunca se le asigno nada...hubo error
        return -1;

    if (mano1.getClase() > mano2.getClase())
        return 1;//claramente gana la mano 1

    if (mano1.getClase() < mano2.getClase())
        return 2;//claramente gana la mano 2

    if (mano1.getClase() == mano2.getClase()) {
        if (mano1.getValorMejor() > mano2.getValorMejor())
            return 1;
        if (mano1.getValorMejor() < mano2.getValorMejor())
            return 2;
        return 0;//empate en clase y valor
    }
    return -1;//de haber algun error
}

void Juego::jugar(string filename) {
    ifstream arch;
    arch.open(filename, ios::in);//"pedidos.csv"
    if (!arch) {
        cout << "Error al abrir el archivo " << filename << endl;
        exit(1);
    }

    ofstream archOUT;
    archOUT.open("salidasP4.txt", ios::out);//"pedidos.csv"
    if (!archOUT) {
        cout << "Error al abrir el archivo " << "salidas2.txt" << endl;
        exit(1);
    }

    archOUT << left << setw(6) << "Mano" << setw(25) << "Jugador 1" << setw(25) << "Jugador 2" << setw(15) << "Ganador" << endl;

    int jugador1 = 0;
    int jugador2 = 0;
    int error = 0;
    int numJugada = 1;
    while (1) {
        mano1.leerMano(arch);
        if (arch.eof())break;
        mano2.leerMano(arch);
        if (arch.eof())break;
        archOUT << left << setw(6) << numJugada;
        mano1.obtenerMejorClase();
        mano2.obtenerMejorClase();
        int comp = comparar(mano1, mano2);
        if (comp == -1) {
            error++;
            cout << setw(15) << "Error" << endl;
            continue;
        }

        resultados(mano1, mano2, comp, archOUT);
        if (comp == 1)
            jugador1++;
        if (comp == 2)
            jugador2++;

        if (comp != 1 && comp != 2)
            error++;

        numJugada++;
    }
    cout << "Respuestas:" << endl;
    cout << "Jugador1:" << jugador1 << endl;
    cout << "Jugador2:" << jugador2 << endl;
    cout << "Errores:" << error << endl;
}

void Juego::resultados(Mano mano1, Mano mano2, int& comp, ofstream& archOUT) {
    bool hubodesempate = false;
    int desempate1 = -1;
    int desempate2 = -1;

    if (comp == 0) {
        hubodesempate = true;
        comp = desempatar(mano1, mano2, desempate1, desempate2);
    }

    string linea1 = mano1.getCartasString();
    string linea2 = mano2.getCartasString();

    archOUT << setw(25) << linea1 << setw(25) << linea2;
    archOUT << setw(5) << comp;
    archOUT << endl;

    archOUT << setw(6) << " ";//tabulacion
    if (mano1.getClase() == 10) {
        archOUT << setw(15) << "ROYAL FLUSH ";
    }
    else if (mano1.getClase() == 9) {
        archOUT << setw(15) << "STRAIGHT FLUSH ";
    }
    else if (mano1.getClase() == 8) {
        archOUT << setw(15) << "FOUR OF A KIND ";
    }
    else if (mano1.getClase() == 7) {
        archOUT << setw(15) << "FULL HOUSE ";
    }
    else if (mano1.getClase() == 6) {
        archOUT << setw(15) << "FLUSH ";
    }
    else if (mano1.getClase() == 5) {
        archOUT << setw(15) << "STRAIGHT ";
    }
    else if (mano1.getClase() == 4) {
        archOUT << setw(15) << "THREE OF A KIND";
    }
    else if (mano1.getClase() == 3) {
        archOUT << setw(15) << "TWO PAIRS ";
    }
    else if (mano1.getClase() == 2) {
        archOUT << setw(15) << "ONE PAIR ";
    }
    else if (mano1.getClase() == 1) {
        archOUT << setw(15) << "HIGH CARD ";
    }
    archOUT << setw(3) << "de ";
    if (mano1.getValorMejor() < 10)
        archOUT << setw(7) << mano1.getValorMejor();
    else {
        if (mano1.getValorMejor() == 10) archOUT << setw(7) << "T";
        else if (mano1.getValorMejor() == 11) archOUT << setw(7) << "J";
        else if (mano1.getValorMejor() == 12) archOUT << setw(7) << "Q";
        else if (mano1.getValorMejor() == 13) archOUT << setw(7) << "K";
        else if (mano1.getValorMejor() == 14) archOUT << setw(7) << "A";
    }

    if (mano2.getClase() == 10) {
        archOUT << setw(15) << "ROYAL FLUSH ";
    }
    else if (mano2.getClase() == 9) {
        archOUT << setw(15) << "STRAIGHT FLUSH ";
    }
    else if (mano2.getClase() == 8) {
        archOUT << setw(15) << "FOUR OF A KIND ";
    }
    else if (mano2.getClase() == 7) {
        archOUT << setw(15) << "FULL HOUSE ";
    }
    else if (mano2.getClase() == 6) {
        archOUT << setw(15) << "FLUSH ";
    }
    else if (mano2.getClase() == 5) {
        archOUT << setw(15) << "STRAIGHT ";
    }
    else if (mano2.getClase() == 4) {
        archOUT << setw(15) << "THREE OF A KIND";
    }
    else if (mano2.getClase() == 3) {
        archOUT << setw(15) << "TWO PAIRS ";
    }
    else if (mano2.getClase() == 2) {
        archOUT << setw(15) << "ONE PAIR ";
    }
    else if (mano2.getClase() == 1) {
        archOUT << setw(15) << "HIGH CARD ";
    }
    archOUT << setw(3) << "de ";
    if(mano2.getValorMejor()<10)
        archOUT << setw(7) << mano2.getValorMejor();
    else {
        if (mano2.getValorMejor() == 10) archOUT << setw(7) << "T";
        else if (mano2.getValorMejor() == 11) archOUT << setw(7) << "J";
        else if (mano2.getValorMejor() == 12) archOUT << setw(7) << "Q";
        else if (mano2.getValorMejor() == 13) archOUT << setw(7) << "K";
        else if (mano2.getValorMejor() == 14) archOUT << setw(7) << "A";
    }
    //se imprime el mejor valor de la mejor clase
    //en los casos de TWO PAIRS, estoy imprimiendo solo el mejor par

    archOUT << endl;

    if (hubodesempate) {
        archOUT << setw(6) << " ";
        archOUT << setw(13) << "Maxima carta " << setw(12) << desempate1;
        archOUT << setw(13) << "Maxima carta " << setw(12) << desempate2;
        archOUT << endl;
    }
}