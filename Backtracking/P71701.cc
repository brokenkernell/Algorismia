#include <iostream>
#include <vector>
#include <string>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VC = vector<char>;
using M = vector<VE>;
using MC = vector<VC>;

int n, r;
MC tauler;

void escriu() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cout << tauler[i][j];
        cout << endl;
    }
    cout << "----------" << endl;
}

bool lliure (int i, int j) {
    if (tauler[i-1][j-1] != '.' or tauler[i-1][j] != '.') return false;
    if (tauler[i][j-1] != '.' or tauler[i][j] != '.') return false;
    if (tauler[i-1][j+1] != '.') return false;
    return true;
}

void f (int i, int j, int rei) {
    if (rei == r) return escriu();
    if (i == n+1 and j == 1) return;
    if (lliure(i, j)) {
        tauler[i][j] = 'K';
        f(i+j/n, j%n+1, rei+1);
        tauler[i][j] = '.';
    }
    f(i+j/n, j%n+1, rei);
}

int main() {
    cin >> n >> r;
    tauler = MC(n+2, VC(n+2, '.'));
    f(1, 1, 0);
}
