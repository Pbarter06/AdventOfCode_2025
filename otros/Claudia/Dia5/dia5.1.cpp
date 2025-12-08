#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<long long,long long>> ranges;
    vector<long long> ids;
    string line;
    bool parsingRanges = true;

    while (getline(cin, line)) {
        if (line.empty()) {
            parsingRanges = false;
            continue;
        }
        if (parsingRanges) {
            size_t dash = line.find('-');
            if (dash != string::npos) {
                long long start = stoll(line.substr(0, dash));
                long long end   = stoll(line.substr(dash+1));
                ranges.push_back({start, end});
            } else {
                long long val = stoll(line);
                ranges.push_back({val, val});
            }
        } else {
            ids.push_back(stoll(line));
        }
    }

    auto isFresh = [&](long long id) {
        for (auto &r : ranges) {
            if (id >= r.first && id <= r.second) return true;
        }
        return false;
    };

    int freshCount = 0;
    for (auto id : ids) {
        if (isFresh(id)) freshCount++;
    }

    cout << "Número de ingredientes frescos: " << freshCount << "\n";
    return 0;
}

