#include <bits/stdc++.h>
using namespace std;

int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, 
                 {0, -1},          {0, 1},
                 {1, -1},  {1, 0}, {1, 1}
};

int main(){
    string line;
    vector<string> grid;

    while(getline(cin, line)){
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();
    
    long long totalRemoved = 0;
    
    while(true){
        vector<pair<int,int>> toRemove;
        
 
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if(grid[i][j] == '@'){
                    int neighbors = 0;
                    for(auto d : dir){
                        int x = i + d[0];
                        int y = j + d[1];
                        if(x >= 0 && x < rows && y >= 0 && y < cols){
                            if(grid[x][y] == '@'){
                                neighbors++;
                            }
                        }
                    }
                    if(neighbors < 4){
                        toRemove.push_back({i, j});
                    }
                }
            }
        }
        
        if(toRemove.empty()) break;
        
        for(auto [i, j] : toRemove){
            grid[i][j] = '.';
        }
        
        totalRemoved += toRemove.size();
    }

    cout << totalRemoved << "\n";
    return 0;
}
