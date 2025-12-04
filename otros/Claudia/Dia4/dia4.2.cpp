#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty()) grid.push_back(line);
    }

    int H = (int)grid.size();
    int W = H ? (int)grid[0].size() : 0;

    int dr[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};

    long long total_removed = 0;

    while (true) {
        vector<pair<int,int> > to_remove;
        for (int r = 0; r < H; r++) {
            for (int c = 0; c < W; c++) {
                if (grid[r][c] != '@') continue;
                int adj = 0;
                for (int k = 0; k < 8; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];
                    if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '@') {
                        adj++;
                    }
                }
                if (adj < 4) {
                    to_remove.push_back(make_pair(r, c));
                }
            }
        }
        if (to_remove.empty()) break;

        for (size_t i = 0; i < to_remove.size(); i++) {
            int r = to_remove[i].first;
            int c = to_remove[i].second;
            grid[r][c] = '.'; // importante: punto y coma
        }
        total_removed += (long long)to_remove.size();
    }

    cout << total_removed << "\n";
    return 0;
}

