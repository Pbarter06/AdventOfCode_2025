#include <bits/stdc++.h>
using namespace std;

//utilizar hash map para no recalcular lo mismo 
int maxDespues(const string& bancobat, int i, unordered_map<int,int>& memo){
    //si ya se ha calculado memo-> evitar volver a repetir la operación
    if(memo.count(i)){
        return memo[i];
    }
    //caso base-> último índice de la cadena
    if(i==(int)bancobat.size()-1){
        //he llegado al final-> devuelvo -1 porque ya no hay más donde seguir
        return memo[i]=-1;
    }
    
    //llamada recursiva para obtener el máximo digito posicicon i+1
    int siguiente= maxDespues(bancobat, i+1, memo);
    //convertir el carácter en número
    int actual= bancobat[i+1]-'0';

    return memo[i]= max(actual, siguiente);
}

//función para encontrar la mayor sacudida
int mejorSacudida(const string& banco){
    unordered_map<int, int>memoMax;
    //inicializar variable para la mayor sacudida
    int mejor=-1;

    //recorrer todas las posiciones posibles
    for(int i=0; i<(int)banco.size();i++){
        int primero=banco[i]-'0';
        //mirar segundo dígito mejor posible después del primero
        int segundo=maxDespues(banco, i, memoMax);

        //no hay segundo dígito válido-> saltar
        if(segundo==-1){
            continue;
        }

        int numero= primero*10+segundo;
        mejor=max(mejor, numero);
    }

    return mejor;
}

int main(){
    //abrir fichero
    ifstream archivo("input.txt");
    //comprobar que se ha abierto correctamente
    if(!archivo.is_open()){
        cout << "Error al abrir el archivo. Intentelo más tarde." << endl;
        return 1;
    }

    string linea;
    long long suma=0;
    while(getline(archivo,linea)){
        if(linea.empty()){
            continue;
        }
        suma+=mejorSacudida(linea);
        }

    cout<<"Suma de la sacudida total= "<<suma<<"\n"<<endl;
    //cerrar fichero
    archivo.close();
    return 0;
}