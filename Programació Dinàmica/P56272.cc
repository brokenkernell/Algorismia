#include <iostream>
#include <vector>
using namespace std;

using VE = vector<long long>;
using MA = vector<VE>;
using VVE = vector<MA>;

VVE taula(50, MA(50, VE(50, -1)));
int r, c;

long long f (int i, int j, int x) {
    if (taula[i][j][x] != -1) return taula[i][j][x];
    if (i == 0) return taula[i][j][x] = 1;
    if (x < c-1) taula[i][j][x] += f(i-1,j, x+1);
    if (x > 0) taula[i][j][x] += f(i-1, j, x-1);
    return taula[i][j][x] += 1;
}


int main () {
    while (cin >> r >> c) {
        long long maneres = 0;
        for (int i = 0; i < c; ++i) maneres += f(r-1, c-1, i);
        cout << maneres << endl;
    }
}

