#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VS = vector<string>;
using Matriu = vector<VE>;

int W, L;
int M = 0;
int inf = 1000000;
VS passadis;
Matriu passes;

int f (int i, int j) {
    if (i == 0 and j == M) return passes[i][j] = 0;
    if (j < 0 or j >= W or i == 0 or passadis[i][j] == '*') return inf;
    if (passes[i][j] != -1) return passes[i][j];
    int aux = min(1 + f(i-1,j-1), min(f(i-1,j), 1 + f(i-1,j+1)));
    if (passadis[i][j] == 'T') return passes[i][j] = 3 + aux;
    return passes[i][j] = aux;
}

int main() {
    cin >> W >> L;
    passadis = VS(L);
    passes = Matriu(L, VE(W, -1));
    for (int i = 0; i < L; ++i) cin >> passadis[i];
    while (passadis[0][M] != 'M') ++M;
    int sol = inf;
    for (int j = 0; j < W; ++j) sol = min(sol, f(L-1,j));
    if (sol == inf) cout << "IMPOSSIBLE" << endl;
    else cout << sol << endl;
}
