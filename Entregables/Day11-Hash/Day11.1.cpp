#include <bits/stdc++.h>
using namespace std;

// Los nodos guardan los nombres ddel dispositivo y las conexiones que tienen
struct Nodo {
    string clave;           
    // donde se conecta
    vector<string> destinos;
    // pasa al siguiente
    Nodo* siguiente;           
    // inicializa los atributos del nodo con los valores recibidos y el puntero siguiente apunta a vacío
    Nodo(string c, vector<string> d) : clave(c), destinos(d), siguiente(nullptr) {}
};

// Clase de tabla hash
class TablaHash {
private:
    // es un vector fijo
    vector<Nodo*> tabla;
    // para el tamaño de la tabla
    int m;              

    // calcula un número para cada palabra sumando sus letras y haciendo el resto con el tamaño de la tabla
    int hashFunc(const string &s) {
        long long suma = 0;
        for (char c : s) suma += (int)c;
        return (int)(suma % m);
    }

public:
    // crea la tabla Hash y le mete todas las posiciones vacías
    TablaHash(int tam) : m(tam) {
        tabla.assign(m, nullptr);
    }

    // inserta un dispositivo en la tabla
    void insertar(const string &clave, const vector<string> &destinos) {
        // se calcula la posición usando la hash
        int idx = hashFunc(clave);
        // se crea un nuevo nodo con los destinos y la clave
        Nodo* nuevo = new Nodo(clave, destinos);
        // si la posición está vacía, se pone ahí directamente
        if (tabla[idx] == nullptr) {
            tabla[idx] = nuevo;
        } else {
            // sino es que hay una colisión por lo que se tiene que recorrer la lista hasta el final
            Nodo* actual = tabla[idx];
            while (actual->siguiente != nullptr) actual = actual->siguiente;
            // se le añade el nuevo nodo al final de la lista
            actual->siguiente = nuevo;
        }
    }

    // busca un dispositivo por nombre
    Nodo* buscar(const string &clave) {
        // se calcula la posición usando la hash y se empieza a mirar desde ahí
        int idx = hashFunc(clave);
        Nodo* actual = tabla[idx];
        // mientras que no esté vacía
        while (actual != nullptr) {
            // si se encuentra la clave que queremos, se devuelve el nodo
            if (actual->clave == clave) return actual;
            // sino, se pasa al siguiente y se hace lo mismo
            actual = actual->siguiente;
        }
        // si no está en ningún lado se devuelve null ( nada )
        return nullptr;
    }
};

// Struct para poder implementar la tabla Memo
// nodo para guardar una clave y su valor (igual que unordered_map pero hecho a mano)
struct NodoMemo {
    // guarda el nombre del nodo (la palabra)
    string clave;
    // guarda el número de caminos calculados para esa clave
    long long valor;
    // puntero al siguiente nodo en caso de colisión (lista enlazada)
    NodoMemo* sig;
    // inicializa la clave, el valor y deja el siguiente a null
    NodoMemo(string c, long long v) : clave(c), valor(v), sig(nullptr) {}
};

// Clase de tabla Memo
class TablaMemo {
private:
    // vector fijo donde cada posición apunta a una lista de nodos
    vector<NodoMemo*> tabla;
    // tamaño de la tabla
    int m;
    // calcula la posición sumando los caracteres y haciendo el resto
    int hashFunc(const string &s) {
        // empieza la suma en 0
        long long suma = 0;
        // se suman los códigos ASCII de cada letra
        for (char c : s) suma += (int)c;
        // se devuelve la posición dentro de la tabla
        return (int)(suma % m);
    }

public:
    // crea la tabla con todas las posiciones vacías
    TablaMemo(int tam) : m(tam) {
        // se rellenan todas las posiciones con null
        tabla.assign(m, nullptr);
    }

    // mira si una clave ya está guardada en la tabla
    bool count(const string &clave) {
        // se calcula la posición donde debería estar
        int idx = hashFunc(clave);
        // se empieza a mirar desde el primer nodo de esa lista
        NodoMemo* act = tabla[idx];
        // mientras haya nodos en la lista
        while (act != nullptr) {
            // si la clave coincide se devuelve true
            if (act->clave == clave) return true;
            // sino se pasa al siguiente nodo
            act = act->sig;
        }
        // si no se encuentra se devuelve false
        return false;
    }

    // devuelve el valor guardado para una clave
    long long get(const string &clave) {
        // se calcula la posición donde debería estar
        int idx = hashFunc(clave);
        // se empieza a mirar desde el primer nodo
        NodoMemo* act = tabla[idx];
        // mientras haya nodos
        while (act != nullptr) {
            // si coincide la clave se devuelve el valor guardado
            if (act->clave == clave) return act->valor;
            // sino se pasa al siguiente
            act = act->sig;
        }
        // esto no debería pasar si se usa bien
        return 0;
    }

    // guarda un valor para una clave (si existe lo actualiza, si no existe lo crea)
    void set(const string &clave, long long valor) {
        // se calcula la posición donde debería ir
        int idx = hashFunc(clave);
        // se mira el primer nodo de esa lista
        NodoMemo* act = tabla[idx];
        // primero se mira si ya existe para actualizarlo
        while (act != nullptr) {
            // si la clave ya está guardada se actualiza el valor
            if (act->clave == clave) {
                act->valor = valor;
                return; // y se termina
            }
            // sino se pasa al siguiente
            act = act->sig;
        }
        // si no existe se crea un nodo nuevo
        NodoMemo* nuevo = new NodoMemo(clave, valor);
        // se engancha al principio de la lista
        nuevo->sig = tabla[idx];
        // y se pone como primer nodo de esa posición
        tabla[idx] = nuevo;
    }
};


// Struct para poder implementar la tabla Set
// nodo para guardar solo la clave
struct NodoSet {
    // guarda la palabra
    string clave;
    // puntero al siguiente nodo en caso de colisión
    NodoSet* sig;
    // inicializa la clave y deja el siguiente a null
    NodoSet(string c) : clave(c), sig(nullptr) {}
};

// Clase de tabla Set
class TablaSet {
private:
    // vector fijo donde cada posición apunta a una lista de nodos
    vector<NodoSet*> tabla;
    // tamaño de la tabla
    int m;

    // calcula la posición sumando los caracteres y haciendo el resto
    int hashFunc(const string &s) {
        // empieza la suma en 0
        long long suma = 0;
        // se suman los códigos ASCII de cada letra
        for (char c : s) suma += (int)c;
        // se devuelve la posición dentro de la tabla
        return (int)(suma % m);
    }

public:
    // crea la tabla con todas las posiciones vacías
    TablaSet(int tam) : m(tam) {
        // se rellenan todas las posiciones con null
        tabla.assign(m, nullptr);
    }

    // mira si una clave está dentro del set
    bool count(const string &clave) {
        // se calcula la posición donde debería estar
        int idx = hashFunc(clave);
        // se empieza a mirar desde el primer nodo
        NodoSet* act = tabla[idx];
        // mientras haya nodos
        while (act != nullptr) {
            // si coincide la clave se devuelve true
            if (act->clave == clave) return true;
            // sino se pasa al siguiente
            act = act->sig;
        }
        // si no se encuentra se devuelve false
        return false;
    }

    // mete la clave si no estaba
    void insert(const string &clave) {
        // si ya está no se mete otra vez
        if (count(clave)) return;
        // se calcula la posición donde debería ir
        int idx = hashFunc(clave);
        // se crea un nodo nuevo con la clave
        NodoSet* nuevo = new NodoSet(clave);
        // se engancha al principio de la lista
        nuevo->sig = tabla[idx];
        // y se pone como primer nodo de esa posición
        tabla[idx] = nuevo;
    }

    // borra la clave del set
    void erase(const string &clave) {
        // se calcula la posición donde debería estar
        int idx = hashFunc(clave);
        // se empieza a mirar desde el primer nodo
        NodoSet* act = tabla[idx];
        // puntero al nodo anterior para poder borrarlo
        NodoSet* prev = nullptr;
        // mientras haya nodos
        while (act != nullptr) {
            // si coincide la clave se borra
            if (act->clave == clave) {
                // si es el primero de la lista
                if (prev == nullptr) tabla[idx] = act->sig;
                // si está en medio o al final
                else prev->sig = act->sig;
                // se borra el nodo
                delete act;
                // y se termina
                return;
            }
            // se avanza al siguiente nodo
            prev = act;
            act = act->sig;
        }
    }
};

// cuenta los caminos desde un nodo hasta "out" (función recursiva)
long long contarCaminos(TablaHash &TH, const string &nodo, TablaMemo &memo, TablaSet &enProceso) {
    // si ha llegado al nodo out ya hay un camino válido
    if (nodo == "out") return 1;        
    // si ya se ha calculado se devuelve el resultado guardado
    if (memo.count(nodo)) return memo.get(nodo); 
    // si el nodo está en proceso significa que está dentro de un bucle por lo que no se cuenta
    if (enProceso.count(nodo)) return 0;  
    // se marca como en proceso
    enProceso.insert(nodo);

    long long total = 0;
    // se busca el nodo en la hash
    Nodo* N = TH.buscar(nodo);
    // si existe se recooren los destinos
    if (N != nullptr) {
        for (auto &dest : N->destinos) {
            // y se suman los caminos que haya en cada destino
            total += contarCaminos(TH, dest, memo, enProceso);
        }
    }
    // se quita de estar en proceso
    enProceso.erase(nodo);
    // se guarda el resultado en memo para que no haya que repstir los cálculos y se devuelve el total
    memo.set(nodo, total);
    return total;
}

int main() {
    // se crea la tabla hash con tamaño fijo (como 101 es primo ayuda a repartir mejor)
    TablaHash TH(101);

    // estructuras para guardar resultados y evitar bucles
    TablaMemo memo(101);
    TablaSet enProceso(101);
    
    string linea;
    // se leen cada línea con las conexiones
    while (getline(cin, linea)) {
        // si la línea está vacía se salta
        if (linea.empty()) continue;

        // se separa la parte antes y después de ':'
        size_t pos = linea.find(':');
        // el nombre del dispositivo
        string clave = linea.substr(0,pos);
        // la lista de destinos
        string resto = linea.substr(pos+1);

        // se quitan los espacios al principio y al final
        auto trim = [](string s){
            // se busca la primera posición que no sea tabulador o espacio
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            // si son todo espacios o tabulador se devuelve una cadena vacía
            if (i==string::npos) return string("");
            // sino, se devuelve el trozo limpio
            return s.substr(i, j-i+1);
        };
        // se aplica la función trim (función que borrará la clave y el resto)
        clave = trim(clave);
        resto = trim(resto);

        // se sacan los destinos y se guardan en un vector
        vector<string> destinos;
        string palabra;
        // isstringstream lee texto como si fuera un archivo del teclado, por eso leerá las palabrasd el texto resto
        istringstream iss(resto);
        // mientras que está leyendo todas las palabras, se meten los destinos en el vector
        while (iss >> palabra) destinos.push_back(palabra);

        // se insertan en la tabla hash
        TH.insertar(clave, destinos);
    }

    // se calculan los caminos desde "you" hasta "out"
    long long resultado = contarCaminos(TH, "you", memo, enProceso);

    // y se muestran el número total de caminos
    cout << resultado << "\n";
    return 0;
}

