#include <bits/stdc++.h>
using namespace std;

struct ProblemBlock {
    int left, right;
};

static string padRight(const string &s, size_t w) {
    string t = s;
    if (t.size() < w) t.resize(w, ' ');
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    size_t width = 0;
    while (getline(cin, line)) {
        width = max(width, line.size());
        lines.push_back(line);
    }
    if (lines.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    for (auto &s : lines) s = padRight(s, width);

    int rows = (int)lines.size();
    int cols = (int)width;

    // Detect separator columns
    vector<bool> isSep(cols, false);
    for (int c = 0; c < cols; ++c) {
        bool sep = true;
        for (int r = 0; r < rows; ++r) {
            if (lines[r][c] != ' ') { sep = false; break; }
        }
        isSep[c] = sep;
    }

    // Build blocks
    vector<ProblemBlock> blocks;
    int c = 0;
    while (c < cols) {
        while (c < cols && isSep[c]) ++c;
        if (c >= cols) break;
        int start = c;
        while (c < cols && !isSep[c]) ++c;
        int end = c - 1;
        blocks.push_back({start, end});
    }

    auto extractNumbers = [&](int topRow, int bottomRow, int left, int right) {
        vector<long long> nums;
        for (int r = topRow; r <= bottomRow; ++r) {
            int col = left;
            while (col <= right) {
                while (col <= right && !isdigit(lines[r][col])) ++col;
                if (col > right) break;
                int start = col;
                while (col <= right && isdigit(lines[r][col])) ++col;
                string token = lines[r].substr(start, col - start);
                nums.push_back(stoll(token));
            }
        }
        return nums;
    };

    auto findOperator = [&](int left, int right) {
        for (int r = rows - 1; r >= 0; --r) {
            for (int cc = left; cc <= right; ++cc) {
                char ch = lines[r][cc];
                if (ch == '+' || ch == '*') return pair<int,char>(r, ch);
            }
        }
        return pair<int,char>(-1, 0);
    };

    long long grandTotal = 0;
    for (auto &blk : blocks) {
        auto [opRow, opChar] = findOperator(blk.left, blk.right);
        if (opRow < 0) continue;
        vector<long long> nums = extractNumbers(0, opRow - 1, blk.left, blk.right);
        if (nums.empty()) continue;

        long long result = (opChar == '*') ? 1LL : 0LL;
        if (opChar == '*') {
            for (auto v : nums) result *= v;
        } else {
            for (auto v : nums) result += v;
        }
        grandTotal += result;
    }

    cout << grandTotal << "\n";
    return 0;
}

