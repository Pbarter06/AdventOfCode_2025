#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

int main() {
    ifstream archivo("dia9.txt");
    if (!archivo) {
        cerr << "No se pudo abrir dia9.txt" << endl;
        return 1;
    }

    vector<pair<int,int>> rojas;
    set<pair<int,int>> conjunto;
    int x,y;
    char coma;

    while (archivo >> x >> coma >> y) {
        rojas.push_back({x,y});
        conjunto.insert({x,y});
    }

    long long maxArea = 0;
    pair<int,int> mejorA, mejorB;

    for (size_t i=0; i<rojas.size(); i++) {
        for (size_t j=i+1; j<rojas.size(); j++) {
            int x1 = rojas[i].first, y1 = rojas[i].second;
            int x2 = rojas[j].first, y2 = rojas[j].second;

            if (x1 != x2 && y1 != y2) {
                pair<int,int> esquina1 = {x1,y2};
                pair<int,int> esquina2 = {x2,y1};

                if (conjunto.count(esquina1) && conjunto.count(esquina2)) {
                    long long area = 1LL * abs(x2-x1) * abs(y2-y1);
                    if (area > maxArea) {
                        maxArea = area;
                        mejorA = rojas[i];
                        mejorB = rojas[j];
                    }
                }
            }
        }
    }

    cout << "Máxima área: " << maxArea << endl;
    if (maxArea > 0) {
        cout << "Entre las baldosas (" << mejorA.first << "," << mejorA.second
             << ") y (" << mejorB.first << "," << mejorB.second << ")" << endl;
    } else {
        cout << "No se encontró ningún rectángulo válido." << endl;
    }

    return 0;
}

