#include <bits/stdc++.h>
using namespace std;

// Estructura que representa un rango [start, end]
struct range{
    long long start;
    long long end;

    // Sobrecarga del operador < para ordenar rangos por inicio
    bool operator<(const range& other) const{
        return start < other.start; 
    }

};

// Merge de rangos: fusiona rangos solapados o adyacentes
vector<range> mergeRanges(vector<range>& ranges){
    if(ranges.empty()) return {}; 

    // Ordenamos para que rangos cercanos queden contiguos
    sort(ranges.begin(), ranges.end());
    
    vector<range> merged;
    merged.push_back(ranges[0]);

    for(size_t i = 1; i < ranges.size(); i++){
        range& last = merged.back();
        const range& current = ranges[i];

        // Si se solapan, extendemos el rango
        if(current.start <= last.end){
            last.end = max(last.end, current.end);
        } else {
            merged.push_back(current);
        }
        
    } return merged;
}

// Búsqueda binaria: cuenta cuántos IDs están dentro de algún rango
long long solve(vector <range>& ranges, vector<long long>& IDS){
    vector<range> merged = mergeRanges(ranges);

    long long fresh_count = 0; 

    for(long long id : IDS){
        bool fresh = false; 
        int left = 0; 
        int right = (int)merged.size() - 1;
        
        // BS para encontrar si el ID está en algún rango
        while(left <= right){
            int mid = left + (right - left) / 2; 
            if(merged[mid].start <= id && id <= merged[mid].end){
                fresh = true; 
                fresh_count++;
                break; 
            } else if(id < merged[mid].start){
                right = mid - 1;  // Buscar en la mitad izquierda
            } else {
                left = mid + 1;   // Buscar en la mitad derecha
            }
        }

    }

    return fresh_count;
}


int main(){

    range ranges_input;
    vector<range> ranges;
    vector<long long> IDS;
    string line;

    // Leer rangos hasta línea vacía
    while(getline(cin, line)){
        if(line.empty()) break; 
        size_t dash_pos = line.find('-');
        ranges_input.start = stoll(line.substr(0, dash_pos));
        ranges_input.end = stoll(line.substr(dash_pos + 1));
        ranges.push_back(ranges_input);
    }
    
    // Leer IDs a consultar
    long long id;
    while(cin >> id){
        IDS.push_back(id);
    }

    // Imprimir cantidad de IDs que están en algún rango
    cout << solve(ranges, IDS) << "\n";

    return 0; 
}