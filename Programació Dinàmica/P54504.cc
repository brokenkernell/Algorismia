#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VE = vector<int>;
using MA = vector<VE>;

VE cartes (500001, -1);

int f (int k) {
    if (k < 0) return 10000;
    if (cartes[k] != -1) return cartes[k];
    if (k == 0) return cartes[k] = 0;
    return cartes[k] = 1 + min(min(f(k-14), f(k-8)), min(f(k-5), f(k-1)));
}


int main () {
    int n;
    while (cin >> n and n != -1) cout << f(n) << endl;
}
