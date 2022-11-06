#include <iostream>//cout
#include <vector>//vector
#include <map>//map
#include <queue>//queue
#include <stdlib.h>//srand,rand
#include <time.h>//time
using namespace std;

void createMaze2d(int);

int main(int argc, char*args[]) {
	createMaze2d(19);
}

void createMaze2d(int n) {
    vector<vector<char>> matriz(n, vector<char>(n));

    //repleto los bordes
    for (int j = 0; j < n; j++)
        matriz[0][j] = '*';

    for (int j = 0; j < n; j++)
        matriz[n - 1][j] = '*';

    for (int i = 0; i < n; i++)
        matriz[i][0] = '*';

    for (int i = 0; i < n; i++)
        matriz[i][n - 1] = '*';
        
    srand(time(NULL));//inicio semilla

    int num;
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            num = rand() % 3 + 1;//genero un numero random entre 1 y 3
            if (num == 1)
                matriz[i][j] = '*';
            else
                matriz[i][j] = ' ';
        }
    }
    matriz[1][1] = 'A';//Aca empieza

    cout << "Maze inicial:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << matriz[i][j];
        cout << endl;
    }

    map<vector<int>, bool> visited;
    vector<int> v(2);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            v[0] = i;
            v[1] = j;
            visited[v] = false;
        }
    }

    queue<vector<int>> cola;
    vector<int> pos(2);
    int count = 0;

    int i = 1;
    int j = 1;
    v[0] = i;
    v[1] = j;
    cola.push(v);
    cout << "Posicion de inicio: [" << i << "][" << j << "]" << endl;
    while (!cola.empty()) {
        pos = cola.front();
        cola.pop();

        if (pos[0] <= 0 || pos[0] >= n - 1 || pos[1] <= 0 || pos[1] >= n - 1) continue;//fuera de limites
        if (matriz[pos[0]][pos[1]] != ' ' && matriz[pos[0]][pos[1]] != 'A') continue;//ya visitado o es barrera. el inicio lo acepto y contare como 1
        if (visited[pos]) continue;

        count++;

        if (matriz[pos[0]][pos[1]] == 'A')
            matriz[pos[0]][pos[1]] = 'A';
        else
            matriz[pos[0]][pos[1]] = 'O';

        visited[pos] = true;

        //ahora pruebo moverme hacia los 4 lados. si es posible, lo encolo.
        if (matriz[pos[0] + 1][pos[1]] == ' ') {
            v[0] = pos[0] + 1;
            v[1] = pos[1];
            cola.push(v);
        }
        if (matriz[pos[0]][pos[1] + 1] == ' ') {
            v[0] = pos[0];
            v[1] = pos[1] + 1;
            cola.push(v);
        }
        if (matriz[pos[0] - 1][pos[1]] == ' ') {
            v[0] = pos[0] - 1;
            v[1] = pos[1];
            cola.push(v);
        }
        if (matriz[pos[0]][pos[1] - 1] == ' ') {
            v[0] = pos[0];
            v[1] = pos[1] - 1;
            cola.push(v);
        }
    }
    cout << "Posicion mas lejana: [" << pos[0] << "][" << pos[1] << "]" << endl;

    //limpio la matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (matriz[i][j] == 'O')
                matriz[i][j] = ' ';
    }
    matriz[pos[0]][pos[1]] = 'B';
    cout << "Maze final:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << matriz[i][j];
        cout << endl;
    }
}