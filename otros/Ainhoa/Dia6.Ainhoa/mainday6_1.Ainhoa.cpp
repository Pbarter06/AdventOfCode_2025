#include <bits/stdc++.h>
using namespace std;

// Recorta espacios
string recortar(const string& s){
    int i = 0, j = (int)s.size() - 1;
    while(i <= j && s[i] == ' ') i++;
    while(j >= i && s[j] == ' ') j--;
    if(i > j) return "";
    return s.substr(i, j - i + 1);
}

// Procesa un bloque en PARTE 2
long long procesarBloqueParte2(const vector<string>& matriz, int filaOperador, int cIni, int cFin){
    // 1. Buscar operador
    char op = 0;
    for(int c = cIni; c <= cFin; c++){
        if(matriz[filaOperador][c] == '+' || matriz[filaOperador][c] == '*'){
            op = matriz[filaOperador][c];
            break;
        }
    }
    if(op == 0) throw runtime_error("Bloque sin operador.");

    // 2. Construir números columna por columna (derecha → izquierda)
    vector<long long> numeros;

    for(int col = cFin; col >= cIni; col--){
        string digitos = "";

        for(int fila = 0; fila < filaOperador; fila++){
            char ch = matriz[fila][col];
            if(ch != ' ') digitos.push_back(ch);
        }

        if(!digitos.empty()){
            long long valor = stoll(digitos);
            numeros.push_back(valor);
        }
    }

    // 3. Aplicar operación
    long long resultado = (op == '+') ? 0 : 1;

    for(long long n : numeros){
        if(op == '+') resultado += n;
        else resultado *= n;
    }

    return resultado;
}

int main(){
    ifstream archivo("input.txt");
    if(!archivo.is_open()){
        cout << "Error al abrir el fichero." << endl;
        return 1;
    }

    vector<string> lineas;
    string linea;

    while(getline(archivo, linea)){
        lineas.push_back(linea);
    }
    archivo.close();

    // Normalizar longitudes
    size_t anchoMax = 0;
    for(const auto& s : lineas) anchoMax = max(anchoMax, s.size());

    vector<string> matriz;
    for(auto s : lineas){
        if(s.size() < anchoMax)
            s += string(anchoMax - s.size(), ' ');
        matriz.push_back(s);
    }

    int filas = matriz.size();
    int columnas = anchoMax;
    int filaOperador = filas - 1;

    // Detectar columnas vacías
    vector<bool> columnaVacia(columnas, true);

    for(int c = 0; c < columnas; c++){
        for(int f = 0; f < filas; f++){
            if(matriz[f][c] != ' '){
                columnaVacia[c] = false;
                break;
            }
        }
    }

    // Encontrar bloques
    vector<pair<int,int>> bloques;
    int c = 0;

    while(c < columnas){
        if(!columnaVacia[c]){
            int ini = c;
            while(c < columnas && !columnaVacia[c]) c++;
            int fin = c - 1;
            bloques.push_back({ini, fin});
        }
        c++;
    }

    // PARTE 2: procesar bloques de derecha a izquierda
    long long total = 0;

    for(int i = (int)bloques.size() - 1; i >= 0; i--){
        auto [ini, fin] = bloques[i];
        long long valor = procesarBloqueParte2(matriz, filaOperador, ini, fin);
        total += valor; // siempre suma entre bloques
    }

    cout << total << endl;
    return 0;
}
