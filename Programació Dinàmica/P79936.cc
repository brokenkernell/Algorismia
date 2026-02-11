#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VS = vector<string>;
using Matriu = vector<VE>;

int c, fil, col;
int maxim = 0;
Matriu colors;

int f (int i, int j, int b) {
    return colors[i-b][j] + colors[i][j-b] - colors[i-b][j-b];
}

void g (int i, int j) {
    if (i < c or j < c) return;
    int valor = colors[i][j] - f(i,j,c);
    if (valor > maxim) {
        maxim = valor;
        fil = i - c;
        col = j - c;
    }
}

int main() {
    int w, h;
    cin >> w >> h >> c;
    colors = Matriu(h+1, VE(w+1, 0));
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            cin >> colors[i][j];
            colors[i][j] += f(i,j,1);
            g(i,j);
        }
    }
    cout << fil << " " << col << endl;
}

