#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Rangos de frescura [inicio, fin]
    vector<pair<long long, long long>> rangos;
    // IDs de ingredientes
    vector<long long> ids;

    string linea;
    bool leyendoRangos = true;

    // Leer entrada: primero rangos, luego IDs
    while (getline(cin, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back(); // limpiar CR si existe

        if (linea.empty()) {
            // Tras la línea en blanco, empiezan los IDs
            leyendoRangos = false;
            continue;
        }

        if (leyendoRangos) {
            size_t guion = linea.find('-');
            if (guion != string::npos) {
                long long inicio = stoll(linea.substr(0, guion));
                long long fin    = stoll(linea.substr(guion + 1));
                rangos.push_back({inicio, fin});
            } else {
                // Valor único como rango [val, val]
                long long val = stoll(linea);
                rangos.push_back({val, val});
            }
        } else {
            ids.push_back(stoll(linea));
        }
    }

    // Comprueba si un id cae dentro de algún rango
    auto esFresco = [&](long long id) -> bool {
        for (const auto& r : rangos) {
            if (id >= r.first && id <= r.second) return true;
        }
        return false;
    };

    // Contar IDs frescos
    int cuentaFrescos = 0;
    for (long long id : ids) {
        if (esFresco(id)) ++cuentaFrescos;
    }

    cout << "Número de ingredientes frescos: " << cuentaFrescos << "\n";
    return 0;
}

