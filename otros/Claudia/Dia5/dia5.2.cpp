#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<long long,long long>> ranges;
    string line;

    // Leer solo hasta la línea en blanco (los rangos)
    while (getline(cin, line)) {
        if (line.empty()) break;
        size_t dash = line.find('-');
        if (dash != string::npos) {
            long long start = stoll(line.substr(0, dash));
            long long end   = stoll(line.substr(dash+1));
            ranges.push_back({start, end});
        } else {
            long long val = stoll(line);
            ranges.push_back({val, val});
        }
    }

    // Ordenar por inicio
    sort(ranges.begin(), ranges.end());

    // Unir rangos solapados
    vector<pair<long long,long long>> merged;
    for (auto &r : ranges) {
        if (merged.empty() || r.first > merged.back().second + 1) {
            merged.push_back(r);
        } else {
            merged.back().second = max(merged.back().second, r.second);
        }
    }

    // Contar IDs distintos
    long long totalFresh = 0;
    for (auto &r : merged) {
        totalFresh += (r.second - r.first + 1);
    }

    cout << "Número total de IDs frescos: " << totalFresh << "\n";
    return 0;
}

