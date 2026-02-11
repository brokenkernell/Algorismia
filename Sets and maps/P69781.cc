#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int INF = 1e8;

int main () {
    int n, x, y;
    while (cin >> x >> y >> n) {
        map<long long, int > seq;
        bool para = false;
        int cont = 1;
        seq[n] = 0;
        while (not para and n <= INF) {
            if (n%2 == 0) {
                n = n/2 + x;
                if (seq.find(n) != seq.end()) {
                    para = true;
                }
                else {
                seq[n] = cont;
                ++cont;
                }
            }
            else {
                n = 3*n + y;
                if (seq.find(n) != seq.end()) {
                    para = true;
                }
                else {
                seq[n] = cont;
                ++cont;
                }
            }
        }
        if (n > INF) cout << n << endl;
        else cout << cont - (seq.find(n) -> second) << endl;
    }
}
