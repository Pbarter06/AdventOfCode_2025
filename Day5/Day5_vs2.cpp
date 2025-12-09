#include <bits/stdc++.h>
using namespace std;


struct range{
    long long start; 
    long long end; 

    bool operator<(const range& other) const{
        return start < other.start; 
    }
};

// Nodo del árbol BST
struct BSTNode {
    range data;
    BSTNode* left;
    BSTNode* right;
    
    BSTNode(const range& r) : data(r), left(nullptr), right(nullptr) {}
};

// Clase para el árbol BST de rangos
class RangeBST {
private:
    BSTNode* root;
    
    BSTNode* insert(BSTNode* node, const range& r) {
        if (node == nullptr) {
            return new BSTNode(r);
        }
        
        if (r.start < node->data.start) {
            node->left = insert(node->left, r);
        } else {
            node->right = insert(node->right, r);
        }
        return node;
    }
    
    bool searchID(BSTNode* node, long long id) const {
        if (node == nullptr) {
            return false;
        }
        
        if (node->data.start <= id && id <= node->data.end) {
            return true;
        }
        
        if (id < node->data.start) {
            return searchID(node->left, id);
        }
        
        return searchID(node->right, id) || searchID(node->left, id);
    }
    
    void deleteTree(BSTNode* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    RangeBST() : root(nullptr) {}
    
    ~RangeBST() {
        deleteTree(root);
    }
    
    void insert(const range& r) {
        root = insert(root, r);
    }
    
    bool contains(long long id) const {
        return searchID(root, id);
    }
};


long long solve(vector<range>& ranges, vector<long long>& IDS){
    RangeBST bst;
    
    for (const auto& r : ranges) {
        bst.insert(r);
    }
    
    long long fresh_count = 0;
    
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

    while(getline(cin, line)){
        if(line.empty()) break; 
        size_t dash_pos = line.find('-');
        ranges_input.start = stoll(line.substr(0, dash_pos));
        ranges_input.end = stoll(line.substr(dash_pos + 1));
        ranges.push_back(ranges_input);
    }
    
    long long id;
    while(cin >> id){
        IDS.push_back(id);
    }

    cout << solve(ranges, IDS) << "\n";

    return 0; 
}