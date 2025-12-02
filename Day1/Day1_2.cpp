#include <iostream>
using namespace std;

struct rotation {
    char dir;
    long long num;
};

int main() {
    long long count = 0;
    int pos = 50;  

    rotation rot;

    while (cin >> rot.dir >> rot.num) {
        long long k = rot.num;

        if (rot.dir == 'R') {
            for (long long i = 0; i < k; i++) {
                pos = (pos + 1) % 100;
                if (pos == 0) count++;
            }
        } 
        else { 
            for (long long i = 0; i < k; i++) {
                pos = (pos - 1 + 100) % 100;
                if (pos == 0) count++;
            }
        }
    }

    cout << count << "\n";
    return 0;
}
