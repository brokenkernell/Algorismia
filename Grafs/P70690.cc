#include<iostream>
#include<vector>
using namespace std;

using VC = vector<char>;
using MC = vector<VC>;

int r, c;
MC mapa;

bool dfs (int i, int j) {
    if (i < 0 or i >= r or j < 0 or j >= c) return false;
    if (mapa[i][j] == 't') return true;
    if (mapa[i][j] == 'X') return false;
    mapa[i][j] = 'X';
    return dfs(i-1,j) or dfs(i+1,j) or dfs(i,j-1) or dfs(i,j+1);
}

int main() {
    cin >> r >> c;
    mapa = MC(r, VC(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) cin >> mapa[i][j];
    }
    int i, j;
    cin >> i >> j;
    cout << (dfs(i-1,j-1) ? "yes" : "no") << endl;
}

