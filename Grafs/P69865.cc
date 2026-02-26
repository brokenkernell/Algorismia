#include<iostream>
#include<vector>
using namespace std;

using VE = vector<int>;
using VC = vector<char>;
using VB = vector<bool>;
using MC = vector<VC>;
using MB = vector<VB>;

int r,c ;
MC T;
MB cav, alf;

const VE dx_a = {1, 1, -1, -1};
const VE dy_a = {1, -1, 1, -1};
const VE dx_c = {-1, -1, -2, -2, 1, 1, 2, 2};
const VE dy_c = {2, -2, 1, -1, 2, -2, 1, -1};

bool fora (int i, int j) {
    return (i < 0) or (i >= r) or (j < 0) or (j >= c);
}

int dfs_alfil (int i, int j) {
    if (fora(i, j) or T[i][j] == 'T' or alf[i][j]) return 0;
    int monedes = 0;
    if (T[i][j] >= '0' and T[i][j] <= '9') {
        monedes = T[i][j] - '0';
        T[i][j] = '.';
    }
    alf[i][j] = true;
    for (int k = 0; k < 4; ++k) monedes += dfs_alfil(i + dx_a[k], j + dy_a[k]);
    return monedes;
}

int dfs_cavall (int i, int j) {
    if (fora(i, j) or T[i][j] == 'T' or cav[i][j]) return 0;
    int monedes = 0;
    if (T[i][j] >= '0' and T[i][j] <= '9') {
        monedes = T[i][j] - '0';
        T[i][j] = '.';
    }
    cav[i][j] = true;
    for (int k = 0; k < 8; ++k) monedes += dfs_cavall(i + dx_c[k], j + dy_c[k]);
    return monedes;
}

int main () {
    while (cin >> r >> c) {
        int monedes = 0;
        T = MC(r, VC(c));
        cav = alf = MB(r, VB(c, false));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) cin >> T[i][j];
        }
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (T[i][j] == 'B') monedes += dfs_alfil(i, j);
                else if (T[i][j] == 'K') monedes += dfs_cavall(i, j);
            }
        }
        cout << monedes << endl;
    }
}
