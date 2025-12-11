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

        Node* getHead() const {
            return head;
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

        bool contains(const string& s1, const string& s2) const {
            bool found1 = false, found2 = false;
            Node* curr = head;
            while (curr != nullptr) {
                if (curr->data == s1) found1 = true;
                if (curr->data == s2) found2 = true;
                curr = curr->next;
            }
            return found1 && found2;
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

    DFS("svr", graph, visited, path, all_paths);

    // Imprimir caminos para debugging
    for (const auto &p : all_paths) {
        p.print();
        cout << '\n';
    }
    cout << "Total caminos: " << all_paths.size() << '\n';

    return 0;
}