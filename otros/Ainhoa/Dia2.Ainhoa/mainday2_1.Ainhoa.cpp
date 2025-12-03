#include <bits/stdc++.h>
using namespace std;

// Generar todas las bases posibles recursivamente
void generarBases(string actual, int maxlong, vector<string>& bases){
    if(actual.size()>0){
        bases.push_back(actual);    // Guardamos la mitad actual
    }
    if(actual.size()==maxlong) return;

    for(char i='0'; i<='9'; i++){   // Añadir dígitos recursivamente
        if(actual.empty() && i=='0') continue;
        generarBases(actual + i, maxlong, bases);
    }
}

// Devolver número repitiendo la base 'x' veces
long long repetir(const string& base, int x){
    string s="";
    for(int j=0; j<x; j++){
        s += base;
    }
    return stoll(s);    // Pasar a número
}

// Comprobar si el número es inválido 
bool esInvalido(long long n){
    string s = to_string(n);
    int L = s.size();

    for(int len=1; len <= L/2; len++){
        if(L % len != 0) continue;
        int x = L / len;
        if(x < 2) continue;

        string base = s.substr(0, len);

        string repetido = "";
        for(int i=0; i<x; i++){
            repetido += base;
        }

        if(repetido == s) return true;
    }
    return false;
}

int main(){
    ifstream archivo("input.txt");
    if(!archivo.is_open()){
        cout << "Error al abrir el archivo. Intentelo más tarde." << endl;
        return 1;
    }

    // rangos
    vector<pair<long long, long long>> rangos;
    string linea;
    getline(archivo, linea);

    stringstream ss(linea);
    string token;
    while(getline(ss, token, ',')){
        size_t guion = token.find('-');
        long long a = stoll(token.substr(0, guion));
        long long b = stoll(token.substr(guion + 1));
        rangos.push_back({a, b});
    }

    // Generar todas las bases posibles
    vector<string> bases;
    generarBases("", 6, bases);  // 6 dígitos de base

    unordered_set<long long> invalidos;

    // Generar candidatos y comprobar validez
    for(const auto& base : bases){
        for(int x=2; x<=10; x++){
            long long candidato;
            try{
                candidato = repetir(base, x);
            } catch(...){
                continue;
            }

            if(candidato < 10) continue;

            if(esInvalido(candidato)){
                for(auto& r : rangos){
                    if(candidato >= r.first && candidato <= r.second){
                        invalidos.insert(candidato);
                    }
                }
            }
        }
    }

    // Sumar todos los inválidos
    long long suma = 0;
    for(long long x : invalidos) suma += x;

    cout << "Suma de inválidos: " << suma << endl;
    archivo.close(); 
    return 0;
}
