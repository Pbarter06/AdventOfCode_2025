#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> grid;
vector<vector<bool>> dp;
int R, C;
long long splits = 0;


//PD
void explore(int r, int c) {
    // Caso base
    if (r >= R || c < 0 || c >= C || dp[r][c]) return;

    //La marcamos como visitada para evitar el sobreconteo de caminos 
    dp[r][c] = true;
    
    if (grid[r][c] == '^') {
        splits++;
        explore(r + 1, c - 1);
        explore(r + 1, c + 1);
    } else {
        explore(r + 1, c);
    }
}

int main() {
    string line;
    int startR = 0, startC = 0;

    while (getline(cin, line)) {
        int pos = line.find('S'); 
        
        if (pos != string::npos) {
            startR = grid.size();
            startC = pos;
        }
        grid.push_back(line);
    }

    R = grid.size();
    C = grid[0].size();
    
    dp.assign(R, vector<bool>(C, false));

    explore(startR, startC);

    cout << splits << endl;
    return 0;
}