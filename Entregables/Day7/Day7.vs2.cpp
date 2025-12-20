#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

int main() {
    vector<string> grid;          // Matriz que almacena el mapa
    string line;
    int startR = 0, startC = 0;   // Posición inicial (donde está 'S')

    // Leer el grid y buscar la posición de inicio 'S'
    while (getline(cin, line)) {
        int pos = line.find('S'); 
        
        if (pos != string::npos) {
            startR = grid.size();
            startC = pos;
        }
        grid.push_back(line);
    }

    int R = grid.size();
    int C = grid[0].size();
    
    // Tabla de visitados para evitar reconteo
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    
    long long splits = 0;
    
    // DFS iterativo usando una pila
    stack<pair<int,int>> pila;
    pila.push({startR, startC});
    
    while (!pila.empty()) {
        auto [r, c] = pila.top();
        pila.pop();
        
        // Verificar límites y si ya fue visitado
        if (r >= R || c < 0 || c >= C || visited[r][c]) continue;
        
        // Marcar como visitado
        visited[r][c] = true;
        
        if (grid[r][c] == '^') {
            // División: contamos y añadimos ambas ramas a la pila
            splits++;
            pila.push({r + 1, c - 1});  // rama izquierda
            pila.push({r + 1, c + 1});  // rama derecha
        } else {
            // Paso normal: añadimos celda de abajo
            pila.push({r + 1, c});
        }
    }

    cout << splits << endl;
    return 0;
}