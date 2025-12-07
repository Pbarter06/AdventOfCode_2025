#include <bits/stdc++.h>
using namespace std;

int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                 {0, -1},          {0, 1},
                 {1, -1},  {1, 0}, {1, 1}
};


int accesibles(vector<string> M){
    
    int acc= 0; 

    for(int i = 0; i < M.size(); i++){
        for(int j = 0; j < M[0].size(); j++){
            if(M[i][j] == '@'){
                int ady = 0; 
                for(auto d : dir){
                    int x = i + d[0]; 
                    int y = j + d[1];

                    if(x >= 0 and x < M.size() and y >= 0 and y < M[0].size()){
                        if(M[x][y] == '@'){
                            ady++; 
                        }

                    }
                } if(ady < 4) acc++; 
            }
        }
    } return acc; 
}



int main (){

    string line; 
    vector<string> M;

    while(getline(cin, line)){
        M.push_back(line); 
    }
    
    cout << accesibles(M) << "\n";
    return 0; 
}