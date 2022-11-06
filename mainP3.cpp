#include <iostream>//cout
#include <iomanip>//setfill
#include <fstream>//files
#include <string>//string
#include <vector>//vector
#include <map>//map
using namespace std;

void listAllTicTacToeGames(string);
void desubicar(vector<vector<char>> &, int);
void ubicar(vector<vector<char>>&, int, char);
char hayGanador(vector<vector<char>>, int);
void functionR(vector<vector<int>>&, vector<char>&, vector<vector<char>>&, int, char, vector<int>&, int , map<int, bool>& );

int main(int argc, char*args[]) {
	listAllTicTacToeGames("respuestasp3.txt");
	return 0;
}

void listAllTicTacToeGames(string fileName) {

    ofstream arch(fileName, ios::out);
    if (!arch) {
        cout << "ERROR: no se puede abrir el archivo " << fileName << endl;
        exit(1);
    }

    vector<vector<int>> global;
    vector<char> resp;
    vector<vector<char>> grid(3, vector<char>(3));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            grid[i][j] = ' ';
    }

    vector<int> plays;
    int count = 0;
    map<int, bool> visited;
    for (int i = 1; i <= 9; i++)
        visited[i] = false;

    for (int i = 1; i <= 9; i++) {
        functionR(global, resp, grid, i, 'X', plays, count, visited);
    }

    arch << "  N    X O X O X O X O X Win" << endl;
    int ind = 0;
    for (vector<int> v : global) {
        arch << setfill('0') << setw(6) << ind + 1 << " ";
        for (int i : v) {
            arch << i << " ";
        }
        arch << resp[ind];
        ind++;
        arch << endl;
    }
}

void desubicar(vector<vector<char>>& grid, int i) {
    i--;
    grid[i / 3][i % 3] = ' ';
}

void ubicar(vector<vector<char>>& grid, int i, char player) {
    i--;
    grid[i / 3][i % 3] = player;
}

char hayGanador(vector<vector<char>> grid, int count) {

    if (count < 3) return 'P';
    //verifico las filas
    if (grid[0][0] != ' ' && grid[0][0] == grid[0][1] && grid[0][1] == grid[0][2]) {
        if (grid[0][0] == 'X')
            return 'X';
        else return 'O';
    }
    if (grid[1][0] != ' ' && grid[1][0] == grid[1][1] && grid[1][1] == grid[1][2]) {
        if (grid[1][0] == 'X')
            return 'X';
        else return 'O';
    }
    if (grid[2][0] != ' ' && grid[2][0] == grid[2][1] && grid[2][1] == grid[2][2]) {
        if (grid[2][0] == 'X')
            return 'X';
        else return 'O';
    }
    //verifico las diagonales
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
        if (grid[0][0] == 'X')
            return 'X';
        else return 'O';
    }
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]) {
        if (grid[0][2] == 'X')
            return 'X';
        else return 'O';
    }
    //verifico las columnas
    if (grid[0][0] != ' ' && grid[0][0] == grid[1][0] && grid[1][0] == grid[2][0]) {
        if (grid[0][0] == 'X')
            return 'X';
        else return 'O';
    }
    if (grid[0][1] != ' ' && grid[0][1] == grid[1][1] && grid[1][1] == grid[2][1]) {
        if (grid[0][1] == 'X')
            return 'X';
        else return 'O';
    }
    if (grid[0][2] != ' ' && grid[0][2] == grid[1][2] && grid[1][2] == grid[2][2]) {
        if (grid[0][2] == 'X')
            return 'X';
        else return 'O';
    }
    return 'P';
}

void functionR(vector<vector<int>>& global, vector<char>& resp, vector<vector<char>>& grid, int i, char player, vector<int>& plays, int count, map<int, bool>& visited) {
    if (visited[i] == true) {
        return;
    }
    if (count > 9) {//no es posible continuar
        return;
    }

    ubicar(grid, i, player);
    visited[i] = true;
    count++;
    plays.push_back(i);
    char letra = hayGanador(grid, count);
    if (letra == 'X' || letra == 'O') {//hay un ganador
        //completo las jugadas faltantes con 0s
        if (count < 9) {
            for (int k = count + 1; k <= 9; k++)
                plays.push_back(0);
        }
        global.push_back(plays);
        //y luego quito lo que le agregué
        if (count < 9) {
            for (int k = count + 1; k <= 9; k++)
                plays.pop_back();
        }
        resp.push_back(letra);//letra del ganador
        desubicar(grid, i);
        visited[i] = false;
        count--;
        plays.pop_back();
        return;
    }
    if (count == 9 && letra == 'P') {//se ha llenado el michi y nadie ha ganado
        global.push_back(plays);
        resp.push_back('E');//EMPATE
        desubicar(grid, i);
        visited[i] = false;
        count--;
        plays.pop_back();
        return;
    }
    if (player == 'X')
        player = 'O';
    else
        player = 'X';

    for (int k = 1; k <= 9; k++) {
        functionR(global, resp, grid, k, player, plays, count, visited);
    }

    desubicar(grid, i);
    visited[i] = false;
    count--;
    plays.pop_back();
}