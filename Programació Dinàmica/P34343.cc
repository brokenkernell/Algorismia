#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VL = vector<long long>;
using ML = vector<VL>;

int z, u;
ML uu(91, VL(91, -1)), zero(91, VL(91, -1)), zerou(91, VL(91, -1));

long long fzero (int z, int u);

long long fzerou (int z, int u) {
    if (z < 0 or u < 0) return 0;
    if (zerou[z][u] != -1) return zerou[z][u];
    if (z <= 1 and u == 1) return zerou[z][u] = 1;
    return zerou[z][u] = fzero(z, u-1);
}

long long fuu (int z, int u) {
    if (z < 0 or u < 0) return 0;
    if (uu[z][u] != -1) return uu[z][u];
    if ( z == 0 and u == 2) return uu[z][u] = 1;
    return uu[z][u] = fzerou(z, u-1);
}

long long fzero (int z , int u) {
    if (z < 0 or u < 0) return 0;
    if (zero[z][u] != -1) return zero[z][u];
    if (z == 1 and u <= 1) return zero[z][u] = 1;
    return zero[z][u] = fzerou(z-1,u) + fuu(z-1,u);
}

int main() {
    while (cin >> z >> u) {
        if (z == 0 and u == 0) cout << 1 << endl;
        else cout << fuu(z,u) + fzerou(z,u) + fzero(z,u) << endl;
    }
}
