#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VS = vector<string>;
using Matriu = vector<VE>;

Matriu expr;

int g (int n, int m) {
    int& res = expr[n][m];
    if (res != 0) return res;
    if (n == 1) return res = m;
    for (int i = 1; i < n-5; i += 2) res += g(i,m)*g(n-5-i,m);
    return res += g(n-2,m);
}

int main() {
    expr = Matriu(26, VE(26, 0));
    int n, m;
    while (cin >> n >> m) {
        if (n%2 == 0) cout << 0 << endl;
        else cout << g(n,m) << endl;
    }
}
