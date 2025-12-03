//day 2 part 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>

using namespace std;

//función recursiva que genera todas las cadenas de dígitos que están
//entre los IDS (sin ceros a la izquierda-> inválidos)
void generarMitades(int medio, string actual, vector<string>& resultado){
    //caso base->si la cadena actual tiene la longitud deseada
    if((int)actual.size()==medio){
        //añadir al vector de resultados
        resultado.push_back(actual);
        return;
    }

    //primer dígito no puede ser 0
    int inicio=(actual.empty()?1:0);    //inicio será 1 para las siguientes posiciones
    for(int i=inicio; i<=9; i++){   //probar todos los dígitos
        generarMitades(medio,actual+char('0' + i), resultado);
    }
}

//función que convierta el string de input a un int
long long repetirMitad(const string& mitad){
    return stoll(mitad+mitad);  //convierte a un entero largo sin desbordamiento
}

//función que compruebe que está dentro del rango permitido [a,b]
bool dentro(long long x, long long a, long long b){
    //devuelve true-> dentro de [a,b]
    return x>=a&&x<=b;  
}

int main(){
    //abrir el fichero input
    ifstream archivo("input.txt");

    //comprobar que se ha abierto correctamente-> lanzar error
    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo. Iténtelo más tarde.\n"<<endl;
        return 1;
    }

    string linea;
    getline(archivo, linea);    //todo el input está en una sola linea
    
    //rangos
    vector<pair<long long, long long>>rangos;   //vector donde guardo rangos pares
    stringstream ss(linea);  //inicializar con la linea para poder partirla por comas
    string token;   //variable para cada rango textual (-)

    while(getline(ss, token, ',')){ //obtener subcadenas separadas por la coma
        size_t guion= token.find('-');   //localiza donde está el -
        long long a=stoll (token.substr(0, guion)); //lo de antes del - límite inferior
        long long b=stoll(token.substr(guion+1));   //límite superior, detrás de -
        rangos.push_back({a,b});    //añade el par al vector de rangos
    }

    //conjunto para alacenar datos sin duplicados
    unordered_set<long long> candidatos;
    int maxlong; //variable que alacena la longitud máxima de numero entre los límites superiores

    for(auto& r: rangos){   //recorre todos los rangos
        //actualizar número d edigitos
        maxlong=max(maxlong, (int)to_string(r.second).size());
    }

    //longitudes pares hasta maslong (solo si tiene longitudes pares)
    for(int totallong=2; totallong<=maxlong; totallong+=2){
        int mitad=totallong/2;
        vector<string> bases;   //vector que guarda todas las mitades
        //llamada recursiva
        generarMitades(mitad, "", bases);
        for(auto& mitadStr : bases){    //para cada mitad generada
            long long num=repetirMitad(mitadStr);
            candidatos.insert(num);
        }
    }

    long long suma=0;   //suma total d elos IDs inválidos
    for(long long x:candidatos){
        for(auto& r: rangos){
            if(dentro(x,r.first,r.second)){
                suma+=x;
                break;
            }
        }
    }
    cout<<"Suma de los IDs inválidos: "<<suma<<"\n"<<endl;
    archivo.close();
    return 0;

}