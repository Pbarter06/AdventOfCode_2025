#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Rangos de frescura [inicio, fin]
    vector<pair<long long, long long>> rangos;
    string linea;

    // Leer solo la primera sección (rangos) hasta línea en blanco
    while (getline(cin, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back(); // limpiar CR si existe
        if (linea.empty()) break;

        size_t guion = linea.find('-');
        if (guion != string::npos) {
            long long inicio = stoll(linea.substr(0, guion));
            long long fin    = stoll(linea.substr(guion + 1));
            rangos.push_back({inicio, fin});
        } else {
            long long val = stoll(linea);
            rangos.push_back({val, val});
        }
    }

    if (rangos.empty()) {
        cout << "Número total de IDs frescos: 0\n";
        return 0;
    }

    // Ordenar por inicio (y por fin para estabilidad)
    sort(rangos.begin(), rangos.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    // Unir rangos solapados o adyacentes
    vector<pair<long long, long long>> unidos;
    for (const auto& r : rangos) {
        if (unidos.empty() || r.first > unidos.back().second + 1) {
            unidos.push_back(r);
        } else {
            unidos.back().second = max(unidos.back().second, r.second);
        }
    }

    // Contar IDs distintos en los rangos unidos
    long long totalFrescos = 0;
    for (const auto& r : unidos) {
        totalFrescos += (r.second - r.first + 1);
    }

    cout << "Número total de IDs frescos: " << totalFrescos << "\n";
    return 0;
}

