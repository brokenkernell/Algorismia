#include<iostream>
#include<vector>
#include<queue>
using namespace std;

using VE = vector<int>;
using VVE = vector<VE>;
using VC = vector<char>;
using VVC = vector<VC>;

int r, c;
VVC mapa;

int dfs (int i, int j) {
    if (i < 0 or i >= r or j < 0 or j >= c or mapa[i][j] == 'X') return 0;
    int tresors = 0;
    if (mapa[i][j] == 't') ++tresors;
    mapa[i][j] = 'X';
    return tresors + dfs(i-1, j) + dfs(i+1, j) + dfs(i, j-1) + dfs(i, j+1);
}

int main() {
    cin >> r >> c;
    mapa = VVC(r, VC(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) cin >> mapa[i][j];
    }
    int i, j;
    cin >> i >> j;
    
    cout << dfs(i-1,j-1) << endl;
}
