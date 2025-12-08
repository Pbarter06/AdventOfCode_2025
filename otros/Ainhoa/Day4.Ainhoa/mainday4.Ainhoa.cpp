#include<bits/stdc++.h>
using namespace std;

int contarRollos (const vector<string>& grid){
    //si el grid está vacía->devolver 0
    if(grid.empty()){
        return 0;
    }
    int filas= grid.size();
    int columnas= grid[0].size();
    int accesibles=0;   //inicializar contador a 0

    //mirar ahora las 8 direcciones posibles
    int direcciones[8][2]={
        {-1,-1},{-1,0},{-1,1},     //arriba izquierda/arriba/arriba-derecha
        {0,-1},          {0,1},      //izquierda/ derecha
        {1,-1},{1,0},{1,1}          //abajo izquierda/abajo/abajo derecha
    };

    //recorrer todas las posiciones del grid
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            //si hay rollo de papel en la posicion actual
            if(grid[i][j]=='@'){
                //contar los rollos de alrededor
                int adyacentes=0;

                for(int d=0; d<8; d++){
                    //calcular posiciones de los vecinos
                    int ni=i+direcciones[d][0];
                    int nj=j+direcciones[d][1];

                    //ver si la posicion actual está dentro del grid
                    if(ni>=0 && ni<filas &&nj>=0 &&nj<columnas){
                        //si hay @ en la posición vecina->sumar 1
                        if(grid[ni][nj]=='@'){
                            adyacentes++;
                        }
                    }
                }
                //si tiene menos de 4 rollos adyacentes-> accesible
                if(adyacentes<4){
                    accesibles++;
                }
            }
        }
    }
    return accesibles;
}

vector<string> visualizarAccesibles(const vector<string>& grid){
    if(grid.empty())return{};

    int filas=grid.size();
    int columnas=grid[0].size();
    vector<string>resultado=grid;
    //mirar ahora las 8 direcciones posibles
    int direcciones[8][2]={
        {-1,-1},{-1,0},{-1,1},     //arriba izquierda/arriba/arriba-derecha
        {0,-1},          {0,1},      //izquierda/ derecha
        {1,-1},{1,0},{1,1}          //abajo izquierda/abajo/abajo derecha
    };

    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            if(grid[i][j]=='@'){
                int adyacentes=0;

                for(int d=0; d<8; d++){
                    int ni=i+direcciones[d][0];
                    int nj=j+direcciones[d][1];

                    if(ni>=0&& ni<filas && nj>=0 && nj<columnas){
                        if(grid[ni][nj]=='@'){
                            adyacentes++;
                        }
                    }
                }
                //ver visualmente qué rollos pueden ser accesibles
                if(adyacentes <4){
                    resultado[i][j]='x';
                }
            }
        }
    }
    return resultado;
}

int main(){
     //abrir input
     ifstream archivo("input.txt");

     //comprobar que se ha abierto correctamente
     if(!archivo.is_open()){
        cout<<"Error al abrir el ficher. Intentelo más tarde."<<endl;
        return 1;
     }

     vector<string> grid;
     string linea;

     while(getline(archivo, linea)){
        if(!linea.empty()){
            grid.push_back(linea);
        }
     }

     if(grid.empty()){
        cout<<"Error al abrir el archivo. El archivo está vacío."<<endl;
        return 1;
     }

     int respuesta= contarRollos (grid);
     cout<<"Respuesta: "<<respuesta<< endl;

     //cerrar el fichero
     archivo.close();
     return 0;
}