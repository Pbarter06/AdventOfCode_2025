#include <bits/stdc++.h>
using namespace std;

const int tableSize = 10009;  


struct cubo{
    int key;     
    char value;      
    bool removed; 
    
    cubo() : key(-1), value('.'), removed(false) {}
};

class HashTable {
    private: 
        cubo table[tableSize]; 
        int cols; 

        int HashFunction(int key){
            unsigned long long k = (unsigned long long) key;
            unsigned long long h = (k * 73856093ULL) % (unsigned long long)tableSize;
            return (int)h;
        }

    public:
        HashTable(int _cols = 1) : cols(_cols) {
            for(int i = 0; i < tableSize; i++){
                table[i] = cubo();
            }
        }
        
        void insert(int row, int col, char value){
            int key = row * cols + col;
            int idx = HashFunction(key); 
            while(table[idx].key != -1 && table[idx].key != key){
                idx = (idx + 1) % tableSize; 
            }
            table[idx].key = key; 
            table[idx].value = value;
            table[idx].removed = false;
        }

        char get(int row, int col){
            int key = row * cols + col;
            int idx = HashFunction(key); 
            while(table[idx].key != -1){
                if(table[idx].key == key && !table[idx].removed){
                    return table[idx].value;
                }
                idx = (idx + 1) % tableSize; 
            }
            return '.';  
        }
        
        void remove(int row, int col){
            int key = row * cols + col;
            int idx = HashFunction(key); 
            while(table[idx].key != -1){
                if(table[idx].key == key){
                    table[idx].removed = true;
                    return;
                }
                idx = (idx + 1) % tableSize; 
            }
        }
        
        bool exists(int row, int col){
            int key = row * cols + col;
            int idx = HashFunction(key); 
            while(table[idx].key != -1){
                if(table[idx].key == key && !table[idx].removed){
                    return true;
                }
                idx = (idx + 1) % tableSize; 
            }
            return false;
        }
};



int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                 {0, -1},          {0, 1},
                 {1, -1},  {1, 0}, {1, 1}
};





int removeAccessible(HashTable& ht, int rows, int cols){
    int removed = 0;
    vector<pair<int,int>> toRemove;  
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(ht.exists(i, j) && ht.get(i, j) == '@'){
                int ady = 0;
                for(auto d : dir){
                    int x = i + d[0];
                    int y = j + d[1];
                    if(x >= 0 && x < rows && y >= 0 && y < cols){
                        if(ht.exists(x, y) && ht.get(x, y) == '@'){
                            ady++;
                        }
                    }
                }
                if(ady < 4){
                    toRemove.push_back({i, j});
                }
            }
        }
    }
    
    for(auto [i, j] : toRemove){
        ht.remove(i, j);
        removed++;
    }
    
    return removed;
}



int main(){
    string line;
    vector<string> M;

    while(getline(cin, line)){
        M.push_back(line);
    }

    int rows = M.size();
    int cols = M[0].size();
    
    HashTable ht(cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            ht.insert(i, j, M[i][j]);
        }
    }

    long long totalRemoved = 0;
    while(true){
        int removed = removeAccessible(ht, rows, cols);
        if(removed == 0) break;
        totalRemoved += removed;
    }

    cout << totalRemoved << "\n";
    return 0;
}