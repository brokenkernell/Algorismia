#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VC = vector<char>;;
using Matriu = vector<VC>;

int n, m, fil1, fil2, col1, col2;
VC V;
Matriu M, camins;

void escriu() {
    for (int i = 0; i < V.size(); ++i) cout << V[i];
        cout << M[fil2][col2] << endl;
}

void g (int f, int c) {
    if ( c < 0 or c >= m or f >= n or f < 0 or not camins[f][c]) return;
    if ( fil2 == f and col2 == c) return escriu();
    camins[f][c] = 0;
    V.push_back(M[f][c]);
    g(f, c-1);
    g(f, c+1);
    g(f+1, c);
    g(f-1, c);
    camins[f][c] = 1;
    V.pop_back();
}

int main () {
    cin >> n >> m;
    M = Matriu(n, VC(m));
    camins = Matriu(n, VC(m, 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> M[i][j];
    }
    cin >> fil1 >> col1 >> fil2 >> col2;
    g(fil1, col1);
}
