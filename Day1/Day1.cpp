#include <bits/stdc++.h>
using namespace std; 

struct rotation{
    char dir; 
    int num; 
};

int main(){
    int cont = 0; 

    //Aritmética modular
    int pos = 50; 

    rotation rot; 
    while(cin >> rot.dir >> rot.num){
        if(rot.dir == 'R'){
            pos = (pos + rot.num) % 100; 
            if (pos == 0) cont++; 
        } else if(rot.dir == 'L'){
            pos = (pos - rot.num + 100) % 100; 
            if (pos == 0) cont++;
        }
        
    }
    cout << cont << "\n";
    return 0;

}