#include <bits/stdc++.h>
using namespace std;

// Estructura que representa un rango [start, end]
struct range{
    long long start; 
    long long end; 

    // Operador para ordenar rangos por su inicio
    bool operator<(const range& other) const{
        return start < other.start; 
    }
};

// Nodo del árbol BST (contiene un rango y punteros a hijos)
struct BSTNode {
    range data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const range& r) : data(r), left(nullptr), right(nullptr) {}
};

// Árbol binario de búsqueda para almacenar rangos
class RangeBST {
private:
    BSTNode* root;
    
    // Inserta un rango en el árbol recursivamente
    BSTNode* insert(BSTNode* node, const range& r) {
        if (node == nullptr) {
            return new BSTNode(r);
        }
        
        // Si el inicio es menor, va a la izquierda; si no, a la derecha
        if (r.start < node->data.start) {
            node->left = insert(node->left, r);
        } else {
            node->right = insert(node->right, r);
        }
        return node;
    }
    
    // Busca si un ID está dentro de algún rango del árbol
    bool searchID(BSTNode* node, long long id) const {
        if (node == nullptr) {
            return false;
        }
        
        // Si el ID está en el rango actual, lo encontramos
        if (node->data.start <= id && id <= node->data.end) {
            return true;
        }
        
        // Si el ID es menor que el inicio, buscar en subárbol izquierdo
        if (id < node->data.start) {
            return searchID(node->left, id);
        }
        
        // Si no, buscar en ambos subárboles (por rangos solapados)
        return searchID(node->right, id) || searchID(node->left, id);
    }
    
    // Libera la memoria del árbol recursivamente
    void deleteTree(BSTNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    RangeBST() : root(nullptr) {}
    
    // Destructor: libera toda la memoria
    ~RangeBST() {
        deleteTree(root);
    }
    
    // Método público para insertar un rango
    void insert(const range& r) {
        root = insert(root, r);
    }
    
    // Método público para verificar si un ID está en algún rango
    bool contains(long long id) const {
        return searchID(root, id);
    }
};

// Resuelve el problema: cuenta cuántos IDs están en algún rango
long long solve(vector<range>& ranges, vector<long long>& IDS){
    RangeBST bst;
    
    // Insertar todos los rangos en el BST
    for (const auto& r : ranges) {
        bst.insert(r);
    }
    
    long long fresh_count = 0;
    
    // Contar cuántos IDs están dentro de algún rango
    for (long long id : IDS) {
        if (bst.contains(id)) {
            fresh_count++;
        }
    }
    
    return fresh_count;
}


int main(){

    range ranges_input;
    vector<range> ranges;
    vector<long long> IDS;
    string line;

    // Leer rangos hasta línea vacía (formato: "inicio-fin")
    while(getline(cin, line)){
        if(line.empty()) break; 
        size_t dash_pos = line.find('-');
        ranges_input.start = stoll(line.substr(0, dash_pos));
        ranges_input.end = stoll(line.substr(dash_pos + 1));
        ranges.push_back(ranges_input);
    }
    
    // Leer los IDs a verificar
    long long id;
    while(cin >> id){
        IDS.push_back(id);
    }

    // Imprimir el resultado
    cout << solve(ranges, IDS) << "\n";

    return 0; 
}