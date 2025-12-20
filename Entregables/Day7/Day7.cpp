#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;          // Matriz que almacena el mapa
vector<vector<bool>> dp;      // Tabla para marcar celdas visitadas (memoización)
int R, C;                     // Dimensiones del grid (filas, columnas)
long long splits = 0;         // Contador de divisiones ('^')


// DFS recursivo con memoización (PD) para explorar el grid
// Exploramos en profundidad antes de retroceder
void explore(int r, int c) {
    // Caso base: fuera de límites o celda ya visitada
    if (r >= R || c < 0 || c >= C || dp[r][c]) return;

    // Marcamos como visitada para evitar sobreconteo de caminos (memoización)
    dp[r][c] = true;
    
    if (grid[r][c] == '^') {
        // División: contamos y exploramos ambas ramas (izq y der)
        splits++;
        // Llamadas recursivas exploran cada rama hasta el fondo
        explore(r + 1, c - 1);  // Rama izquierda
        explore(r + 1, c + 1);  // Rama derecha
    } else {
        // Seguimos profundizando en el camino actual
        explore(r + 1, c);
    }
    // Al terminar las llamadas recursivas, "retrocede" automáticamente
}

int main() {
    string line;
    int startR = 0, startC = 0;  // Posición inicial (donde está 'S')

    // Leer el grid y buscar la posición de inicio 'S'
    while (getline(cin, line)) {
        int pos = line.find('S'); 
        
        if (pos != string::npos) {
            startR = grid.size();
            startC = pos;
        }
        grid.push_back(line);
    }

    R = grid.size();
    C = grid[0].size();
    
    // Inicializar tabla de visitados en false
    dp.assign(R, vector<bool>(C, false));

    // Iniciar DFS desde la posición inicial
    explore(startR, startC);

    // Imprimir total de divisiones encontradas
    cout << splits << endl;
    return 0;
}