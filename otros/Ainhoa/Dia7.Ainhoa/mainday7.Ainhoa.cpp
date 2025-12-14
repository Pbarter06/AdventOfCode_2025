#include <bits/stdc++.h>
using namespace std;

// Estructura para representar un haz
struct Haz {
    int fila, col;
};


int main() {
    //abrir el input
    ifstream archivo("input.txt");
    //comprobar que se ha abierto correctamente
    if(!archivo.is_open()){
        cout << "Error al abrir el fichero." << endl;
        return 1;
    }

    vector<string> matriz;
    string linea;

    while(getline(archivo, linea)){
        matriz.push_back(linea);
    }

    int filas = matriz.size();
    int cols = matriz[0].size();

    //buscar S
    int colS = -1;
    for(int c = 0; c < cols; c++){
        if(matriz[0][c] == 'S'){
            colS = c;
            break;
        }
    }

    if(colS == -1){
        cout << "No se encontró S." << endl;
        return 1;
    }

    //cola de haces activos
    queue<Haz> cola;
    cola.push({0, colS});

    long long divisiones = 0;

    //evitar duplicados
    set<pair<int,int>> visitado;

    //Simulación
    while(!cola.empty()){
        Haz h = cola.front();
        cola.pop();

        int f = h.fila;
        int c = h.col;

        //avanzar hacia abajo
        int nf = f + 1;
        int nc = c;

        //Si sale del mapa-> desaparece
        if(nf >= filas) continue;

        char celda = matriz[nf][nc];

        if(celda == '.'){
            //sigue bajando
            if(!visitado.count({nf, nc})){
                visitado.insert({nf, nc});
                cola.push({nf, nc});
            }
        }
        else if(celda == '^'){
            // División
            divisiones++;

            // Haz izquierdo
            if(nc - 1 >= 0){
                if(!visitado.count({nf, nc - 1})){
                    visitado.insert({nf, nc - 1});
                    cola.push({nf, nc - 1});
                }
            }

            // Haz derecho
            if(nc + 1 < cols){
                if(!visitado.count({nf, nc + 1})){
                    visitado.insert({nf, nc + 1});
                    cola.push({nf, nc + 1});
                }
            }
        }
    }
    archivo.close();
    cout << divisiones << endl;
    return 0;
}
