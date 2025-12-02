#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
    //abrir archivo con las rotaciones de la caja fuerte
    ifstream archivo("input.txt");

    //verificar si se ha abierto bien
    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo. Inténtelo más tarde."<<endl;
        return 1;
    }

    //problema a solucionar
    //mirar en la posición inicial del dial
    int dial_ini=50;    //siempre empieza en 50

    //contraseña real-> nº veces que el dial apunta a 0
    int contador=0;

    //leer cada línea del input
    string l_contrasenya;

    // Procesar cada rotación del archivo
    while (getline(archivo, l_contrasenya)) {
        // Saltar líneas vacías
        if (l_contrasenya.empty()) {
            continue;
        }

        //ver si el primer caracter es L o R (para saber hacia donde rotar el dial)
        char giro= l_contrasenya[0];

        //convertir el resto de cadena de string-> entero
        int dist= stoi(l_contrasenya.substr(1));

        //calcular posiciones
        if(giro=='L'){  //izquierda
            //restar
            dial_ini=(dial_ini-dist)%100;
            //mirar si está en el rango permitido de [0,99]
            if(dial_ini<0){
                //para que esté en el rango
                dial_ini+=100;
            }
        }
        else if(giro=='R'){ //derecha
            //sumar
            dial_ini=(dial_ini+dist)%100;
        }

        //verificar si después de la rotación el dial apunta a 0 (actualizar contador)
        if(dial_ini==0){
            contador++;
        }


    }
    //cerrar el archivo
    archivo.close();
    cout<<"Contraseña: "<<contador<<endl;
    return 0;
}