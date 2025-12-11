#include <bits/stdc++.h>
using namespace std;

//Esrtuctura de datos
struct Node {
    string data;
    Node* next;

    Node(string val) : data(val), next(nullptr) {}
};


//Clase: Lista enlazada -> Nos servirá para almacenar todos los caminos de "you" hasta "out"
class LinkedList {
    private:
        Node* head;
        int n = 0; //num de elementos

    public:
        LinkedList() : head(nullptr) {}

        void insert(int pos, string e) {
            if (pos < 0 || pos > n) {
                throw std::out_of_range("Fuera de rango1");
            }

            if (pos == 0) {
                Node* node = new Node(e);
                node->next = head;
                head = node;
            } else {
                Node* prev = head;
                for (int i = 0; i < pos - 1; i++) prev = prev->next;
                Node* node = new Node(e);
                node->next = prev->next;
                prev->next = node;
            }
            n++;
        }

        int getSize() const {
            return n;
        }

        void print() const {
            Node* curr = head;
            bool first = true;
            while (curr != nullptr) {
                if (!first) cout << " -> ";
                cout << curr->data;
                curr = curr->next;
                first = false;
            }
        }

        void removeLast() {
            if (n == 0) return;
            if (n == 1) {
                delete head;
                head = nullptr;
                n = 0;
                return;
            }
            Node* curr = head;
            for (int i = 0; i < n - 2; i++) curr = curr->next;
            delete curr->next;
            curr->next = nullptr;
            n--;
        }

        LinkedList copy() const {
            LinkedList result;
            Node* curr = head;
            int pos = 0;
            while (curr != nullptr) {
                result.insert(pos, curr->data);
                curr = curr->next;
                pos++;
            }
            return result;
        }

        bool search(string e){
            Node* cur = head;
            for (int i = 0; i < n; i++) {
                if (cur->data == e) return true;
                cur = cur->next;
            }
            return false;
        }

};


//DFS para encontrar todos los caminos de "you" hasta "out"
//Además se usa unordered_map para representar el grafo -> unordered_map(key, contenido) -> Tablas Hash
void DFS(const string& curr, unordered_map<string, vector<string>>& graph, 
         unordered_map<string, bool>& visited, LinkedList& path, 
         vector<LinkedList>& all_paths) {
    visited[curr] = true;
    path.insert(path.getSize(), curr);

    if (curr == "out" && path.search("fft") && path.search("dac")) {
        all_paths.push_back(path.copy());
    } else {
        for (const string& neighbor : graph[curr]) {
            if (!visited[neighbor]) {
                DFS(neighbor, graph, visited, path, all_paths);
            }
        }
    }

    // Backtrack
    path.removeLast();
    visited[curr] = false;
}

// Optimized DP using integer ids (más rápido que usar strings en recursión)
// Devuelve un array de 4 elementos con el número de caminos desde `u` hasta `target`
// index = mask: bit0 = contiene "fft", bit1 = contiene "dac".
array<long long,4> dp_count_int(int u, int target, const vector<vector<int>>& g,
                                const vector<char>& isFFT, const vector<char>& isDAC,
                                vector<array<long long,4>>& memo, vector<char>& state) {
    if (state[u] == 2) return memo[u];
    if (state[u] == 1) return {0,0,0,0}; // ciclo -> 0 contribuciones para evitar infinitos

    state[u] = 1; // visiting
    array<long long,4> res = {0,0,0,0};

    if (u == target) {
        int m = (isFFT[u] ? 1 : 0) | (isDAC[u] ? 2 : 0);
        res[m] = 1;
        state[u] = 2;
        memo[u] = res;
        return res;
    }

    for (int v : g[u]) {
        array<long long,4> child = dp_count_int(v, target, g, isFFT, isDAC, memo, state);
        for (int m = 0; m < 4; ++m) {
            int newm = m | (isFFT[u] ? 1 : 0) | (isDAC[u] ? 2 : 0);
            res[newm] += child[m];
        }
    }

    state[u] = 2; // done
    memo[u] = res;
    return res;
}


int main(){
    unordered_map<string, vector<string>> graph;
    string line;
    LinkedList path;
    vector<LinkedList> all_paths;
    unordered_map<string, bool> visited;

    // Leer entrada
    while (getline(cin, line)) {
        size_t pos = line.find(':');
        string from = line.substr(0, pos);
        stringstream ss(line.substr(pos + 1));
        string to;
        
        while (ss >> to) {
            graph[from].push_back(to);
            if (graph.find(to) == graph.end()) graph[to] = {};
        }
    }

    // Inicializar visited para DFS (usaremos DFS también para listar caminos)
    for (auto &p : graph) visited[p.first] = false;
    // Ejecutar DFS desde "svr" para obtener las rutas concretas que contienen fft y dac
    DFS("svr", graph, visited, path, all_paths);

    // Construir mapeo string->int para acelerar DP
    unordered_map<string,int> id;
    vector<string> names;
    id.reserve(graph.size()*2);
    for (auto &p : graph) {
        if (id.find(p.first) == id.end()) {
            id[p.first] = (int)names.size(); names.push_back(p.first);
        }
        for (auto &v : p.second) {
            if (id.find(v) == id.end()) {
                id[v] = (int)names.size(); names.push_back(v);
            }
        }
    }

    int n = (int)names.size();
    vector<vector<int>> g(n);
    for (auto &p : graph) {
        int u = id[p.first];
        for (auto &v : p.second) g[u].push_back(id[v]);
    }

    vector<char> isFFT(n, 0), isDAC(n, 0);
    for (int i = 0; i < n; ++i) {
        if (names[i] == "fft") isFFT[i] = 1;
        if (names[i] == "dac") isDAC[i] = 1;
    }

    // Usar DP desde "svr" para contar de forma óptima
    if (id.find("svr") == id.end() || id.find("out") == id.end()) {
        cout << "DP count (fft & dac) from svr to out: 0\n";
    } else {
        int start = id["svr"]; int target = id["out"];
        vector<array<long long,4>> memo2(n);
        vector<char> state2(n, 0);
        array<long long,4> ans = dp_count_int(start, target, g, isFFT, isDAC, memo2, state2);
        cout << "DP count (fft & dac) from svr to out: " << ans[3] << '\n';
    }

    // Imprimir caminos encontrados por DFS (ya filtrados)
    for (const auto &p : all_paths) {
        p.print();
        cout << '\n';
    }
    cout << "Total caminos (DFS filtered): " << all_paths.size() << '\n';

    return 0;
}