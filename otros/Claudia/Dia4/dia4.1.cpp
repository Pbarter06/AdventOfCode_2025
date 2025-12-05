#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> g;
    string s;
    while (getline(cin, s)) {
        if (!s.empty() && (s.back()=='\r')) s.pop_back();
        if (!s.empty()) g.push_back(s);
    }
    int H = g.size();
    int W = H ? g[0].size() : 0;
    auto in = [&](int r,int c){ return r>=0 && r<H && c>=0 && c<W; };
    int dr[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};
    long long accessible = 0;
    for (int r=0;r<H;r++){
        for (int c=0;c<W;c++){
            if (g[r][c] != '@') continue;
            int adj = 0;
            for (int k=0;k<8;k++){
                int nr = r+dr[k], nc = c+dc[k];
                if (in(nr,nc) && g[nr][nc]=='@') adj++;
            }
            if (adj < 4) accessible++;
        }
    }
    cout << accessible << "\n";
    return 0;
}

