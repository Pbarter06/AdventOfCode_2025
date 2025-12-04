#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream file("dia3.txt");
    if (!file) {
        cerr << "No se pudo abrir el archivo dia3.txt" << endl;
        return 1;
    }

    string line;
    long long total = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        // Precalcular el máximo dígito a la derecha para cada posición
        int n = (int)line.size();
        vector<int> maxRight(n, -1);
        int currentMax = -1;
        for (int i = n - 1; i >= 0; --i) {
            maxRight[i] = currentMax;
            currentMax = max(currentMax, line[i] - '0');
        }

        int maxJoltage = 0;
        for (int i = 0; i < n; ++i) {
            int A = line[i] - '0';
            int B = maxRight[i];
            if (B != -1) {
                int val = A * 10 + B;
                if (val > maxJoltage) maxJoltage = val;
            }
        }

        total += maxJoltage;
    }

    cout << "Total output joltage: " << total << endl;
    return 0;
}

