#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using ME = vector<VE>;

int n, res;
VE pesos, v;

int f (int i, int k) {
    if (i < 0) return 0;
    if (k == n) return 1;
    
    int res = 0;
    for (int j = 0; j < n; ++j) {
        if (not v[j]) {
            v[j] = 1;
            res += f(i + pesos[j], k+1);
            res += f(i - pesos[j], k+1);
            v[j] = 0;
        }
    }
    return res;
}

int main () {
    while (cin >> n) {
        v = VE(n, 0);
        pesos = VE(n);
        for (int i = 0; i < n; ++i) cin >> pesos[i];
        cout << f(0,0) << endl;
    }
}

