#include<bits/stdc++.h>
using namespace std;

//funcion para fusionar los rangos
vector<pair<long long, long long>> fusionarRangos(vector<pair<long long, long long>>& rangos){
    if(rangos.empty()) return {};
    //ordenar por  ini
    sort(rangos.begin(), rangos.end());
    vector<pair<long long, long long>> fusionados;
    long long ini= rangos[0].first;
    long long fin= rangos[0].second;

    for(size_t i=1; i<rangos.size(); i++){
        long long a= rangos[i].first;
        long long b=rangos[i].second;

        if(a<=fin+1){
            //se solapan o son contiguos
            fin= max(fin, b);
        }
        else{
            //no se solapan-> guardar el intervalo actual
            fusionados.push_back({ini, fin});
            ini=a;
            fin=b;
        }
    }
    //añadir el último intervalo
    fusionados.push_back({ini,fin});
    return fusionados;
}

//función para ver si un id es fresco
bool esFresco(long long id, const vector<pair<long long, long long>>& rangos){
    for(auto& r: rangos){
        if(id>= r.first && id<=r.second){
            return true;
        }
        if(r.first>id){
            return false;
        }
    }
    return false;
}

int main(){
    vector<pair<long long, long long>> rangos;
    vector<long long> ids;

    //abrir el fichero
    ifstream archivo("input.txt");

    //comprobar que seha abierto bien
    if(!archivo.is_open()){
        cout<<"Error al abrir el fichero. Intentelo más tarde."<<endl;
    }

    string linea;
    //leer todos los rangos
    while(getline(archivo,linea)){
        if(linea.empty()){
            break;
        }

        size_t guion= linea.find ('-');
        long long a= stoll(linea.substr(0, guion));
        long long b= stoll(linea.substr(guion+1));
        rangos.push_back({a,b});
    }


    //leer los ID que faltan
    while(getline(archivo,linea)){
        if(!linea.empty()){
            ids.push_back(stoll(linea));
        }
    }

    auto fusionados= fusionarRangos(rangos);
    int contador=0;
    for(long long id:ids){
        if(esFresco(id,fusionados)){
            contador++;
        }
    }

    archivo.close();
    cout<<"Número de ID frescos: "<<contador<<endl;
    return 0;
}