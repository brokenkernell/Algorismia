include <iostream>
#include <vector>
#include <string>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VC = vector<char>;
using M = vector<VE>;

int n, v, x;
VC par;

void escriu() {
    for (int i = 0; i < n; ++i) cout << par[i];
    cout << endl;
}

void f (int i, int voc, int cons) {
    if (voc > v or i - voc > n - v or (n - i) - (v - voc) >= v - voc + 2) return;
    if (i == n) return escriu();
    for (int j = 0; j < x; ++j) {
        if (j == 0 or j == 4 or j == 8 or j == 14 or j == 20) {
            par[i] = 'a' + j;
            f(i+1, voc+1, 0);
        }
        else if (not cons) {
            par[i] = 'a' + j;
            f(i+1, voc, 1);
        }
    }
}

int main() {
    cin >> n >> v >> x;
    par = VC(n);
    f(0, 0, 0);
}
