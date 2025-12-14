#include <bits/stdc++.h>
using namespace std;


struct range{
    long long start; 
    long long end; 


    //Regla de comparacion 
    bool operator<(const range& other) const{
        return start < other.start; 
    }

};


vector<range> mergeRanges(vector<range>& ranges){
    if(ranges.empty()) return {}; 

    sort(ranges.begin(), ranges.end());
    vector<range> merged;
    merged.push_back(ranges[0]);

    //MERGE
    for(size_t i = 1; i < ranges.size(); i++){
        range& last = merged.back(); 
        const range& current = ranges[i]; 

        if(current.start <= last.end){
            last.end = max(last.end, current.end);
        } else {
            merged.push_back(current);
        }
        
    } return merged;
}


long long solve(vector <range>& ranges){
    vector<range> merged = mergeRanges(ranges);

    long long fresh = 0; 
    
    for(int i = 0; i < merged.size(); i++){
        fresh += (merged[i].end - merged[i].start + 1);
    }

    return fresh;
}


int main(){

    range ranges_input;
    vector<range> ranges;
    string line;

    while(getline(cin, line)){
        if(line.empty()) break; 
        size_t dash_pos = line.find('-');
        ranges_input.start = stoll(line.substr(0, dash_pos));
        ranges_input.end = stoll(line.substr(dash_pos + 1));
        ranges.push_back(ranges_input);
    }
    

    cout << solve(ranges) << "\n";

    return 0; 
}