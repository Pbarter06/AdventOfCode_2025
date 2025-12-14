#include <bits/stdc++.h>
using namespace std;

// Cada nodo guarda el nombre del dispositivo y sus conexiones
struct Nodo {
    string clave;               // nombre del aparato
    vector<string> destinos;    // a dónde se conecta
    Nodo* siguiente;            // siguiente en la lista si hay colisión
    Nodo(string c, vector<string> d) : clave(c), destinos(d), siguiente(nullptr) {}
};

// Clase de tabla hash
class TablaHash {
    vector<Nodo*> tabla; // vector fijo
    int m;               // tamaño de la tabla

    // Función hash sencilla: suma de letras % tamaño
    int hashFunc(const string &s) {
        long long suma = 0;
        for (char c : s) suma += (int)c;
        return (int)(suma % m);
    }

public:
    TablaHash(int tam) : m(tam) {
        tabla.assign(m, nullptr);
    }

    // Insertar un dispositivo en la tabla
    void insertar(const string &clave, const vector<string> &destinos) {
        int idx = hashFunc(clave);
        Nodo* nuevo = new Nodo(clave, destinos);
        if (tabla[idx] == nullptr) {
            tabla[idx] = nuevo;
        } else {
            // colisión -> encadenamiento
            Nodo* actual = tabla[idx];
            while (actual->siguiente != nullptr) actual = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    // Buscar un dispositivo por nombre
    Nodo* buscar(const string &clave) {
        int idx = hashFunc(clave);
        Nodo* actual = tabla[idx];
        while (actual != nullptr) {
            if (actual->clave == clave) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }
};

// Función recursiva para contar caminos desde un nodo hasta "out"
long long contarCaminos(TablaHash &TH, const string &nodo,
                        unordered_map<string,long long> &memo,
                        unordered_set<string> &enProceso) {
    if (nodo == "out") return 1;          // si llegamos a "out", es un camino válido
    if (memo.count(nodo)) return memo[nodo]; // si ya lo calculamos, lo devolvemos
    if (enProceso.count(nodo)) return 0;  // si hay bucle, no cuenta

    enProceso.insert(nodo);

    long long total = 0;
    Nodo* N = TH.buscar(nodo);
    if (N != nullptr) {
        for (auto &dest : N->destinos) {
            total += contarCaminos(TH, dest, memo, enProceso);
        }
    }

    enProceso.erase(nodo);
    memo[nodo] = total;
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Creamos la tabla hash con tamaño fijo (101 es primo, ayuda a repartir mejor)
    TablaHash TH(101);

    string linea;
    // Leemos cada línea del fichero con las conexiones
    while (getline(cin, linea)) {
        if (linea.empty()) continue;

        // Separamos la parte antes y después de ':'
        size_t pos = linea.find(':');
        string clave = linea.substr(0,pos);
        string resto = linea.substr(pos+1);

        // Quitamos espacios
        auto trim = [](string s){
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if (i==string::npos) return string("");
            return s.substr(i, j-i+1);
        };
        clave = trim(clave);
        resto = trim(resto);

        // Sacamos los destinos (aparatos conectados)
        vector<string> destinos;
        string palabra;
        istringstream iss(resto);
        while (iss >> palabra) destinos.push_back(palabra);

        // Insertamos en la tabla hash
        TH.insertar(clave, destinos);
    }

    // Estructuras auxiliares para guardar resultados y evitar bucles
    unordered_map<string,long long> memo;
    unordered_set<string> enProceso;

    // Calculamos los caminos desde "you" hasta "out"
    long long resultado = contarCaminos(TH, "you", memo, enProceso);

    // Mostramos el número total de caminos
    cout << resultado << "\n";
    return 0;
}

