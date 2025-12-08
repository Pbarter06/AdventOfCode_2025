#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<string> M; 
    string line; 
    
    while(getline(cin, line)){
        M.push_back(line); 
    }
    
    int rows = M.size();
    int cols = 0;
    for(const auto& row : M) cols = max(cols, (int)row.size());
    
    vector<pair<int,int>> problems;
    int start = 0;
    
    for(int col = 0; col <= cols; col++){
        bool blank = (col == cols);
        if(col < cols){
            blank = true;
            for(int row = 0; row < rows; row++){
                if(col < (int)M[row].size() && M[row][col] != ' '){
                    blank = false;
                    break;
                }
            }
        }
        
        if(blank && col > start){
            problems.push_back({start, col - 1});
            start = col + 1;
        }
    }
    
    long long total = 0;
    
    for(auto [sc, ec] : problems){
        vector<long long> nums;
        char op = ' ';
        
        for(int row = 0; row < rows - 1; row++){
            string num = "";
            for(int col = sc; col <= ec; col++){
                if(col < (int)M[row].size() && isdigit(M[row][col])){
                    num += M[row][col];
                } else if(!num.empty()){
                    nums.push_back(stoll(num));
                    num = "";
                }
            }
            if(!num.empty()) nums.push_back(stoll(num));
        }
        
        for(int col = sc; col <= ec; col++){
            if(col < (int)M[rows-1].size() && (M[rows-1][col] == '+' || M[rows-1][col] == '*')){
                op = M[rows-1][col];
                break;
            }
        }
        
        if(!nums.empty() && op != ' '){
            long long res = nums[0];
            for(size_t i = 1; i < nums.size(); i++){
                if(op == '+') res += nums[i];
                else res *= nums[i];
            }
            total += res;
        }
    }
    
    cout << total << "\n";
    return 0; 
}