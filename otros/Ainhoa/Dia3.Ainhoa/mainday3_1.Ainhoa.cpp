#include<bits/stdc++.h>
using namespace std;

// encontrar los mejores k dígitos desde la posición i
// memo[i][k] = el mejor número de k dígitos que se puede formar desde la posición i en adelante
map<pair<int,int>, string> memo;

string mejoresDesdePosicion(const string& banco, int pos, int digitos_restantes) {
    // Si no quedan dígitos por seleccionar, devolver cadena vacía
    if (digitos_restantes == 0) {
        return "";
    }
    
    // Si no hay suficientes dígitos disponibles, imposible
    if (pos + digitos_restantes > (int)banco.size()) {
        return "";
    }
    
    // Verificar si ya está calculado
    pair<int,int> clave = {pos, digitos_restantes};
    if (memo.count(clave)) {
        return memo[clave];
    }
    
    string mejor = "";
    
    // Probar tomar cada posición desde 'pos' hasta donde sea posible
    // Dejar suficientes dígitos para completar los restantes
    int limite = banco.size() - digitos_restantes + 1;
    
    for (int i = pos; i < limite; i++) {
        // Tomar el dígito en la posición i
        string actual(1, banco[i]);
        
        // Obtener los mejores (digitos_restantes - 1) dígitos después de i
        string resto = mejoresDesdePosicion(banco, i + 1, digitos_restantes - 1);
        
        // Si no se pudo completar, saltar
        if (digitos_restantes > 1 && resto.empty()) {
            continue;
        }
        
        string candidato = actual + resto;
        
        // Comparar lexicográficamente (que es equivalente a numéricamente para strings de igual longitud)
        if (mejor.empty() || candidato > mejor) {
            mejor = candidato;
        }
    }
    
    memo[clave] = mejor;
    return mejor;
}

long long mejorSacudida(const string& banco) {
    memo.clear();
    
    // Encontrar los mejores 12 dígitos
    string resultado = mejoresDesdePosicion(banco, 0, 12);
    
    if (resultado.empty()) {
        return 0;
    }
    
    // Convertir a número
    return stoll(resultado);
}

int main() {
    ifstream archivo("input.txt");
    
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo. Inténtelo más tarde." << endl;
        return 1;
    }

    string linea;
    long long suma = 0;
    
    while (getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }
        
        long long sacudida = mejorSacudida(linea);
        cout << "Línea: " << linea << " -> Sacudida: " << sacudida << endl;
        suma += sacudida;
    }

    cout << "\nSuma de la sacudida total = " << suma << endl;
    
    archivo.close();
    return 0;
}