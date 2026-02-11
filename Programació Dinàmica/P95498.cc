#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VS = vector<string>;
using Matriu = vector<VE>;

int n, m;
VE v, u;
Matriu M;

int f (int k, int p) {
    if (k < 0  or p < 0) return 0;
    if (M[k][p] != -1) return M[k][p];
    if (v[k] == u[p]) return M[k][p] = 1 + f(k-1,p-1);
    return M[k][p] = max( f(k-1,p), f(k,p-1) );
}

int main() {
    while (cin >> m >> n) {
        v = VE(m);
        u = VE(n);
        for (int i = 0; i < m; ++i) cin >> v[i];
        for (int j = 0; j < n; ++j) cin >> u[j];
        M = Matriu(m, VE(n, -1));
        cout << f(m-1,n-1) << endl;
    }
}
