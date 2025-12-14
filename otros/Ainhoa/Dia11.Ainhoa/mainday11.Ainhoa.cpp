#include<bits/stdc++.h>
using namespace std;


class Nodo{
    public:
        string nombre;  //nombre del nodo
        vector<Nodo*> siguiente;    //apunto al siguiente nodo

        //crear el método constructor con el nombre
        Nodo(const string& nombre): nombre(nombre){}

        //función que añade una salida del nodo hacia otro (nodo)
        void nextnodo(Nodo* otro){
            //meter al final del vector el otro nodo
            siguiente.push_back(otro);
        }

};

class Grafo{
    public:
    unordered_map<string, Nodo*> nodos;     //diccionario asocia el nombre del nodo con el puntero

    //devuelve un puntero al nodo con es enombre (o lo crea)
    Nodo* crearNodo(const string& nombre){
        if(nodos.find(nombre)==nodos.end()){  //si no existe aún -> crear nuevo nodo
            nodos[nombre]= new Nodo(nombre);
        }
        //si existe-> devolver el puntero del nodo
        return nodos[nombre];
    }

    //función que une el nodo origen (org) hacia el resto de los destinos (fnl)
    void unirNodos(const string& org, const vector<string>& fnl){
        //obtiene (o crea si no existe) el nodo origen
        Nodo* orgNodo= crearNodo(org);
        for(const string& destino: fnl){    //recorrer toda la lista
            //obtener su nodo de cada destino
            Nodo* fnlNodo= crearNodo(destino);
            orgNodo-> nextnodo(fnlNodo);    //añadir arista
        }
    }

    void Camino(Nodo* nactual, Nodo* final, vector<string>& camino, vector<vector<string>>&todosCaminos, int& contadorCaminos){
            //si no hemos llegado al nodo objetivo
        if(nactual==final){
            //guardar copia del camino actual
            todosCaminos.push_back(camino);
            contadorCaminos++;
            return;
        }

        for(Nodo* nxt: nactual->siguiente){ //recorrer todas las salidas del nodo actual
            //añadir nombre del siguiente nodo al camino actual
            camino.push_back(nxt->nombre);
            //llamada recursiva->para  deshacer el último paso del camino
            Camino(nxt, final, camino, todosCaminos, contadorCaminos);
            camino.pop_back();
        }
    }

    //función que devuelve un vector de caminos con los nombres de los nodos
    vector<vector<string>> encontrarTodosCaminos(const string& start, const string& end, int& contadorCaminos){
       //crear vector que acumule todos los caminos desde start hasta end
        vector<vector<string>> todosCaminos;
        //camino actual
        vector<string> camino;

        //obtener nodos de inicio y de final
        Nodo* startNodo= nodos[start];
        Nodo* endNodo= nodos[end];

        //inicializar contador de caminos
        contadorCaminos=0;

        if(!startNodo|| !endNodo){
            return todosCaminos;
        }

        //explorar los caminos desde el inicio hasta el final
        camino.push_back(startNodo->nombre);
        Camino(startNodo, endNodo, camino, todosCaminos, contadorCaminos);

        return todosCaminos;    //lista completa de caminos encontrados
    }

};

Grafo parseInput(const vector<string>& lines){
    Grafo g;    //grafo vacío

    for(const string& lin: lines){  //recorrer todas las líneas del vector
        if(lin.empty()){   //si la línea está vacía-> saltar
            continue;
        }

        //separar variables
        string derecha, izquierda;
        stringstream ss(lin);

        //Guardar la parte izquierda de la linea
        getline(ss, izquierda, ':');
        getline(ss, derecha);

        string izq= izquierda;  //guardar la parte izquierda en la variable izq
        vector<string> l;

        //Guardar la parte derecha de la línea
        stringstream ss2(derecha);
        string aux;
        while(ss2>>aux){    //leer palabra por palabra
            //guardar en la variable l
            l.push_back(aux);
        }

        //añade al grafo las nuevas uniones
        g.unirNodos(izq, l);
    }

    return g;
}

int main(){
    ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir input.txt. Inténtelo más tarde." << endl;
        return 1;
    }
    vector<string> lines;
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty())
            lines.push_back(linea);
    }

    // Construir grafo
    Grafo g = parseInput(lines);

    int contadorCaminos=0;

    //buscar caminos desde you hasta out
    vector<vector<string>> caminos= g.encontrarTodosCaminos("you","out", contadorCaminos);
    cout << "Numero total de caminos (contador): " << contadorCaminos << "\n";
    cout << "Numero total de caminos (size):     " << caminos.size() << "\n\n";

    //mostrar caminos
    // Mostrar caminos
    for (const auto& p : caminos) {
        for (size_t i = 0; i < p.size(); i++) {
            cout << p[i];
            if (i + 1 < p.size()) cout << " -> ";
        }
        cout << "\n";
    }

    archivo.close();
    return 0;
}