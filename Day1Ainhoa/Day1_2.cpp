#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
    // abrir archivo con las rotaciones de la caja fuerte
    ifstream archivo("input.txt");
    
    // Verificar si se ha abierto bien
    if(!archivo.is_open()){
        cout<<"Error al abrir el archivo. Inténtelo más tarde."<<endl;
        return 1;
    }
    
    // Posición inicial del dial
    int dial_ini = 50;
    
    // Contador de veces que pasa por 0 (método 0x434C49434B)
    int contador = 0;
    
    // Leer cada línea del input
    string l_contrasenya;
    
    // Procesar cada rotación del archivo
    while (getline(archivo, l_contrasenya)) {
        // Saltar líneas vacías
        if (l_contrasenya.empty()) {
            continue;
        }
        
        // Extraer dirección (L o R) para saber para donde rota el dial
        char giro = l_contrasenya[0];
        
        // Extraer distancia
        int dist = stoi(l_contrasenya.substr(1));
        
        // Clave: Contar cuántas veces pasamos por 0 durante la rotación
        
        if(giro == 'L'){  // Izquierda 
            // Calcular posición final-> restar
            int posicion_final = (dial_ini - dist) % 100;
            if(posicion_final < 0){     //si es negativo
                posicion_final += 100;
            }
            
            // Contar cuántas veces pasamos por 0
            // Si vamos de posición mayor a menor y cruzamos el 0:
            // Casos:
            // 1. Si posicion > 0 y posicion_final < posicion: puede que pasemos por 0
            // 2. Si damos vueltas completas: distancia / 100
            
            // Vueltas completas
            contador += dist / 100;
            
            // Verificar si cruzamos el 0 en la vuelta parcial
            int distancia_parcial = dist % 100;
            if(distancia_parcial > 0){
                // Simulamos el movimiento en la vuelta parcial
                int temp = dial_ini;
                for(int i = 0; i < distancia_parcial; i++){
                    temp--;
                    if(temp < 0) {
                    temp = 99;
                    }
                    if(temp == 0){
                     contador++;
                    }
                }
            }
            
            dial_ini = posicion_final;
        }
        else if(giro== 'R'){  // Derecha
            // Calcular posición final
            int posicion_final = (dial_ini + dist) % 100;
            
            // Vueltas completas
            contador += dist / 100;
            
            // Verificar si cruzamos el 0 en la vuelta parcial
            int distancia_parcial = dist % 100;
            if(distancia_parcial > 0){
                // Simulamos el movimiento en la vuelta parcial
                int temp = dial_ini;
                for(int i = 0; i < distancia_parcial; i++){
                    temp++;
                    if(temp > 99){
                    temp = 0;
                    }
                    if(temp == 0){
                    contador++;
                    }
                }
            }
            
            dial_ini = posicion_final;
        }
    }
    
    // Cerrar el archivo
    archivo.close();
    
    cout<<"Contraseña (método 0x434C49434B): "<<contador<<endl;
    
    return 0;
}
