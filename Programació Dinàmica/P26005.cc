#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using MA = vector<VE>;

VE cost;
MA dinamica;

string p1, p2;

int buidar (int i, int j) {
    int aux = 0;
    for (int k = i; k >= 0; --k) aux += cost[p1[k] - 'a'];
    for (int k = j; k >= 0; --k) aux += cost[p2[k] - 'a'];
    return aux;
}

int f (int i, int j) {
    if (i < 0 and j < 0) return 0;
    if (i < 0 or j < 0) return buidar(i, j);
    int& res = dinamica[i][j];
    if(res !=-1) return res;
    if (p1[i] == p2[j]) return res = f(i-1, j-1);
    return res = min(cost[p1[i]-'a'] + f(i-1, j), cost[p2[j]- 'a'] + f(i, j-1));
}

int main () {
    int n;
    while (cin >> n) {
        cost = VE(n);
        for (int i = 0; i < n; ++i) cin >> cost[i];
        cin >> p1 >> p2;
        int n1 = p1.size(); int n2 = p2.size();
        dinamica = MA(n1, VE(n2, -1));
        cout << f(n1-1,n2-1) << endl;
    }
}

