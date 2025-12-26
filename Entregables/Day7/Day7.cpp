#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;               // Matriz que almacena el mapa
vector<vector<long long>> dp;      // Tabla de memoización: dp[r][c] = splits desde (r,c), -1 si no calculado
int R, C;                          // Dimensiones del grid (filas, columnas)


// DFS recursivo con memoización (PD) para explorar el grid
// Devuelve el número de splits nuevos encontrados desde la celda (r, c)
// Si la celda ya ha sido visitada, devuelve 0 (los splits ya han sido contados)
long long explore(int r, int c) {
    // Caso base: fuera de límites, no hay splits
    if (r >= R || c < 0 || c >= C) return 0;

    // Memoización: si ya hemos calculado esta celda, devolvemos el valor guardado (0)
    // Esto evita contar los mismos splits múltiples veces
    if (dp[r][c] >= 0) return dp[r][c];

    long long resultado;
    
    if (grid[r][c] == '^') {
        // División: contamos 1 split + los splits NUEVOS de ambas ramas
        resultado = 1 + explore(r + 1, c - 1) + explore(r + 1, c + 1);
    } else {
        // Seguimos profundizando en el camino actual
        resultado = explore(r + 1, c);
    }
    
    // Guardamos el resultado en la tabla de memoización
    // La próxima vez que lleguemos aquí, devolveremos 0 (ya contados)
    dp[r][c] = 0;
    return resultado;
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
    
    // Inicializar tabla de memoización con -1 (no calculado)
    dp.assign(R, vector<long long>(C, -1));

    // Iniciar DFS desde la posición inicial y obtener el total de splits
    long long resultado = explore(startR, startC);

    // Imprimir total de divisiones encontradas
    cout << resultado << endl;
    return 0;
}