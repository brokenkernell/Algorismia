#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VE = vector<int>;
using MA = vector<VE>;

MA dinamica;
string w;

int f (int i, int j) {
    if (dinamica[i][j] != -1) return dinamica[i][j];
    if (i >= j) return dinamica[i][j] = 0;
    if (w[i] == w[j]) return dinamica[i][j] = f(i+1, j-1);
    
    return dinamica[i][j] = min(1 + f(i + 1, j), 1 + f(i, j - 1));
}


int main () {
    while (cin >> w) {
        int n = w.size();
        dinamica = MA(n, VE(n, -1));
        if (f(0, n-1) == 0) cout << "Passes the Dislex-Wonga test" << endl;
        else cout << dinamica[0][n-1] << endl;
    }
}
