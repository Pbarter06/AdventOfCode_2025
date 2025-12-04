#include<bits/stdc++.h>
using namespace std;

// cuenta cuántos vecinos @ tiene una posición
int contarVecinos(const vector<string>& grid, int i, int j) {
    int filas = grid.size();
    int columnas = grid[0].size();
    int vecinos = 0;
    
    //mirar ahora las 8 direcciones posibles
    int direcciones[8][2]={
        {-1,-1},{-1,0},{-1,1},     //arriba izquierda/arriba/arriba-derecha
        {0,-1},          {0,1},      //izquierda/ derecha
        {1,-1},{1,0},{1,1}          //abajo izquierda/abajo/abajo derecha
    };
    
    for (int d = 0; d < 8; d++) {
        int ni = i + direcciones[d][0];
        int nj = j + direcciones[d][1];
        
        if (ni >= 0 && ni < filas && nj >= 0 && nj < columnas) {
            if (grid[ni][nj] == '@') {
                vecinos++;
            }
        }
    }
    
    return vecinos;
}

// parte 1 del día 4-> contar rollos accesibles en el estado actual
int contarRollosAccesibles(const vector<string>& grid) {
    if (grid.empty()) return 0;
    
    int filas = grid.size();
    int columnas = grid[0].size();
    int accesibles = 0;
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (grid[i][j] == '@') {
                if (contarVecinos(grid, i, j) < 4) {
                    accesibles++;
                }
            }
        }
    }
    
    return accesibles;
}

// parte 2 del día 4-> elimina todos los rollos accesibles y cuenta total eliminado
int eliminarRollosIterativo(vector<string>& grid) {
    if (grid.empty()) return 0;
    
    int filas = grid.size();
    int columnas = grid[0].size();
    int totalEliminados = 0;
    
    // Repetir mientras haya rollos accesibles
    while (true) {
        // Encontrar todos los rollos accesibles en esta iteración
        vector<pair<int,int>> accesibles;
        
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (grid[i][j] == '@') {
                    if (contarVecinos(grid, i, j) < 4) {
                        accesibles.push_back({i, j});
                    }
                }
            }
        }
        
        // Si no hay más accesibles, terminar
        if (accesibles.empty()) {
            break;
        }
        
        // Eliminar todos los rollos accesibles encontrados
        for (auto pos : accesibles) {
            grid[pos.first][pos.second] = '.';
        }
        
        totalEliminados += accesibles.size();
        
        // Opcional: mostrar progreso
        // cout << "Eliminados en esta ronda: " << accesibles.size() << endl;
    }
    
    return totalEliminados;
}

// Visualizar el grid actual
void mostrarGrid(const vector<string>& grid) {
    for (const auto& linea : grid) {
        cout << linea << endl;
    }
}

int main() {
    ifstream archivo("input.txt");
    
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir input.txt" << endl;
        return 1;
    }
    
    vector<string> grid;
    string linea;
    
    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            grid.push_back(linea);
        }
    }
    archivo.close();
    
    if (grid.empty()) {
        cout << "Error: El archivo está vacío" << endl;
        return 1;
    }
    
    // PARTE 1: Contar rollos accesibles en el estado inicial
    int parte1 = contarRollosAccesibles(grid);
    cout << "Parte 1 - Rollos accesibles inicialmente: " << parte1 << endl;
    
    // PARTE 2: Eliminar iterativamente todos los rollos posibles
    // Hacemos una copia del grid porque lo vamos a modificar
    vector<string> gridCopia = grid;
    int parte2 = eliminarRollosIterativo(gridCopia);
    cout << "Parte 2 - Total de rollos eliminados: " << parte2 << endl;
    
    // Opcional: mostrar estado final
    // cout << "\nEstado final del grid:" << endl;
    // mostrarGrid(gridCopia);
    
    return 0;
}