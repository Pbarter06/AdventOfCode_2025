#include <bits/stdc++.h>
using namespace std;

//estructura para representar una línea temporal activa
struct Estado {
    int fila, col;
};

int main(){
    ifstream archivo("input.txt");
    if(!archivo.is_open()){
        cout << "Error al abrir el fichero." << endl;
        return 1;
    }

    vector<string> matriz;
    string linea;

    while(getline(archivo, linea)){
        matriz.push_back(linea);
    }
    archivo.close();

    //NORMALIZAR TODAS LAS LÍNEAS A LA MISMA LONGITUD
    int filas = matriz.size();
    int cols = 0;

    for(const auto& s : matriz)
        cols = max(cols, (int)s.size());

    for(auto& s : matriz)
        if(s.size() < cols)
            s += string(cols - s.size(), ' ');

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

    //  uso un MAP que cuenta cuántas líneas temporales llegan a cada celda
    map<pair<int,int>, long long> activos;
    activos[{0, colS}] = 1;  // una sola partícula inicial

    //conjunto de estados finales (pero con contador)
    map<pair<int,int>, long long> finales;

    //hacer simulación
    while(!activos.empty()){
        map<pair<int,int>, long long> nuevos;

        for(auto [pos, cantidad] : activos){
            int f = pos.first;
            int c = pos.second;

            int nf = f + 1;
            int nc = c;

            // Si sale del mapa → línea temporal finaliza
            if(nf >= filas){
                finales[{f, c}] += cantidad;
                continue;
            }

            char celda = matriz[nf][nc];

            if(celda == '^'){
                // División cuántica: dos líneas temporales
                if(nc - 1 >= 0)
                    nuevos[{nf, nc - 1}] += cantidad;
                if(nc + 1 < cols)
                    nuevos[{nf, nc + 1}] += cantidad;
            }
            else {
                // Cualquier otra cosa → sigue recto
                nuevos[{nf, nc}] += cantidad;
            }
        }

        activos = nuevos;
    }

    //La respuesta es la suma de TODAS las líneas temporales finales
    long long totalLineas = 0;
    for(auto& [pos, cantidad] : finales){
        totalLineas += cantidad;
    }

    cout << totalLineas << endl;

    return 0;
}


