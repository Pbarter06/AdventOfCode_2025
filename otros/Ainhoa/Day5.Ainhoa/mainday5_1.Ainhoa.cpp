#include <bits/stdc++.h>
using namespace std;

// función para fusionar los rangos
vector<pair<long long, long long>> fusionarRangos(vector<pair<long long, long long>>& rangos){
    if(rangos.empty()) return {};
    sort(rangos.begin(), rangos.end());
    vector<pair<long long, long long>> fusionados;
    long long ini = rangos[0].first;
    long long fin = rangos[0].second;

    for(size_t i = 1; i < rangos.size(); i++){
        long long a = rangos[i].first;
        long long b = rangos[i].second;

        if(a <= fin + 1){
            fin = max(fin, b);
        }
        else{
            fusionados.push_back({ini, fin});
            ini = a;
            fin = b;
        }
    }

    fusionados.push_back({ini, fin});
    return fusionados;
}

int main(){
    vector<pair<long long, long long>> rangos;

    ifstream archivo("input.txt");

    if(!archivo.is_open()){
        cout << "Error al abrir el fichero. Inténtelo más tarde." << endl;
        return 1;
    }

    string linea;

    // Leer todos los rangos (hasta línea en blanco)
    while(getline(archivo, linea)){
        if(linea.empty()){
            break;
        }

        size_t guion = linea.find('-');
        long long a = stoll(linea.substr(0, guion));
        long long b = stoll(linea.substr(guion + 1));
        rangos.push_back({a, b});
    }

    // Fusionar rangos
    auto fusionados = fusionarRangos(rangos);

    // Contar todos los IDs frescos
    long long totalFrescos = 0;
    for(const auto& r : fusionados){
        totalFrescos += (r.second - r.first + 1);
    }

    archivo.close();
    cout << "Número total de IDs frecsos: " << totalFrescos << endl;
    return 0;
}


