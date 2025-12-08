#include <bits/stdc++.h>
using namespace std;

//Función que recorta espacios por izquierda y derecha
string recortar(const string& s){
    int i = 0, j = (int)s.size() - 1;
    while(i <= j && s[i] == ' ') i++;
    while(j >= i && s[j] == ' ') j--;
    if(i > j) return "";
    return s.substr(i, j - i + 1);
}

// aplicar Divide y vencerás:
// funcíon que procesa un rango de columnas (un bloque) y devuelve su valor
long long procesarBloque(const vector<string>& matriz, int filaOperador, int cIni, int cFin){
    // 1. Buscar operador en la última fila del bloque
    char op = 0;
    for(int c = cIni; c <= cFin; c++){
        if(matriz[filaOperador][c] == '+' || matriz[filaOperador][c] == '*'){
            op = matriz[filaOperador][c];
            break;
        }
    }

    if(op == 0){
        throw runtime_error("Bloque sin operador detectado.");
    }

    // 2. Extraer números del bloque
    vector<long long> numeros;
    for(int f = 0; f < filaOperador; f++){
        string sub = matriz[f].substr(cIni, cFin - cIni + 1);
        sub = recortar(sub);
        if(!sub.empty()){
            numeros.push_back(stoll(sub));
        }
    }

    // 3. Calcular resultado
    long long resultado = (op == '+') ? 0 : 1;

    for(long long n : numeros){
        if(op == '+') resultado += n;
        else resultado *= n;
    }

    return resultado;
}

int main() {
    //abrir el archivo
   ifstream archivo("input.txt");

   //comprobar que se ha abierto bien
    if(!archivo.is_open()){
        cout << "Error al abrir el fichero. Inténtelo más tarde." << endl;
        return 1;
    }

    vector<string> lineas;
    string linea;

    // Leer todas las líneas del fichero
    while(getline(archivo, linea)){
        lineas.push_back(linea);
    }

    // Normalizar longitudes
    size_t anchoMax = 0;
    for(const auto& s : lineas) anchoMax = max(anchoMax, s.size());

    vector<string> matriz;
    for(auto s : lineas){
        if(s.size() < anchoMax){
            s += string(anchoMax - s.size(), ' ');
        }
        matriz.push_back(s);
    }

    int filas = matriz.size();
    int columnas = anchoMax;
    int filaOperador = filas - 1;

    // Detectar columnas completamente vacías
    vector<bool> columnaVacia(columnas, true);

    for(int c = 0; c < columnas; c++){
        for(int f = 0; f < filas; f++){
            if(matriz[f][c] != ' '){
                columnaVacia[c] = false;
                break;
            }
        }
    }

    // Encontrar bloques de columnas no vacías
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

    // Procesar cada bloque
    long long total = 0;

    for(const auto& b : bloques){
        long long valor = procesarBloque(matriz, filaOperador, b.first, b.second);
        total += valor;
    }
    
    //cerrar el fichero
    archivo.close();
    // Mostrar resultado final
    cout << total << endl;

    return 0;
}
