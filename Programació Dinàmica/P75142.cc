#include <iostream>
#include <vector>
using namespace std;

using VE = vector<long long>;
using VVE = vector<VE>;

VVE comb(26, VE(26, -1));
VVE stirl(26, VE(26, -1));

long long c (int n, int y) {
    if (comb[n][y] != -1) return comb[n][y];
    if (y > n) return comb[n][y] = 0;
    if (y == 0 or y == n) return comb[n][y] = 1;
    return comb[n][y] = c(n-1, y-1) + c(n-1, y);
}

long long s (int k, int x) {
    if (k < 0) return 0;
    if (stirl[k][x] != -1) return stirl[k][x];
    if (x > k or (x == 0 and k > 0)) return stirl[k][x] = 0;
    if (x == 1 or x == k) return stirl[k][x] = 1;
    return stirl[k][x] = x*s(k-1, x) + s(k-1, x-1);
}

int main () {
    int n, x, y;
    while (cin >> n >> x >> y) cout << c(n, y)*s(n-y, x) << endl;
}
