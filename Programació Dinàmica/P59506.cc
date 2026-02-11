#include <iostream>
#include <vector>
using namespace std;

using VE = vector<long long>;
using MA = vector<VE>;

MA cong0(31, VE(31, -1));
MA cong1(31, VE(31, -1));
MA cong2(31, VE(31, -1));

long long cong_1(int z, int u);

long long cong_0 (int z, int u) {
    if (cong0[z][u] != -1) return cong0[z][u];
    if (z == 0 or u == 0) return cong0[z][u] = (u+1)%2;
    return cong0[z][u] = cong_0(z-1, u) + cong_1(z, u-1);
}

long long cong_2 (int z, int u) {
    if (cong2[z][u] != -1) return cong2[z][u];
    if (z == 0 or u == 0) return cong2[z][u] = 0;
    return cong2[z][u] = cong_1(z-1, u) + cong_2(z, u-1);
}

long long cong_1 (int z, int u) {
    if (cong1[z][u] != -1) return cong1[z][u];
    if (z == 0 or u == 0) return cong1[z][u] = u%2;
    return cong1[z][u] = cong_2(z-1, u) + cong_0(z, u-1);
}

int main () {
    int z, u;
    while (cin >> z >> u) cout << cong_0(z, u) << endl;
}
