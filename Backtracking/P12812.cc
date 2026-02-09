#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using VE = vector<int>;

VE V;
int n;

void escriu() {
    for (int i = 0; i < n; ++i) cout << (i ? " ": "") << V[i];
    cout << endl;
}

void f (int p) {
    if (p == n) return escriu();
    else {
        V[p] = 0;
        f(p+1);
        V[p] = 1;
        f(p+1);
    }
}

int main() {
    cin >> n;
    V = VE(n, 0);
    f(0);
}
