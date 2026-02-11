#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<ll> VL;
typedef vector<VL> VVL;
typedef vector<VVL> VVVL;
typedef vector<int> VI;
typedef vector<char> VC;
typedef vector<VC> VVC;

int R, C, L, pi, pj;
VVC T;
VVVL F_S, F_N;
VI inc_i = { -2, -2, -2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 };
VI inc_j = { -2, -1, 0, 1, 2, -2, -1, 0, 1, 2, -2, -1, 1, 2, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2 };

// true si (i,j) es una posicio valida del vector
bool dins(int i, int j) {
    if (i < 0 or i >= R or j < 0 or j >= C) return false;
    return true;
}

// omple amb 'o' totes les posicions amb presencia d'un Old One
void old(int i, int j) {
    for (int k = 0; k < 24; ++k) {
        if (dins(i + inc_i[k], j + inc_j[k])) T[i + inc_i[k]][j + inc_j[k]] = 'O';
    }
}

ll f_N(int i, int j, int l);

// maneres d'anar de (i,j) fins P amb l moviments laterals si a la fila i ja ens hem mogut lateralment
ll f_S(int i, int j, int l) {
    if (pi == i and pj == j and l == 0 and T[i][j] != 'O') return 1;
    if (i == R) return 0;
    ll& res = F_S[i][j][l];
    if (res != -1) return res;
    if (i >= pi or T[i][j] == 'O') return res = 0;
    return res = f_N(i + 1, j, l);
}

// maneres d'anar de (i,j) fins P amb l moviments laterals si a la fila i NO ens hem mogut lateralment
ll f_N(int i, int j, int l) {
    if (pi == i and pj == j and l == 0 and T[i][j] != 'O') return 1;
    if (i == R) return 0;
    ll& res = F_N[i][j][l];
    if (res != -1) return res;
    if (i > pi or T[i][j] == 'O') return res = 0;
    res = 0;
    if (l > 0) {
        int k = j;
        while (--k >= 0 and T[i][k] != 'O') res += f_S(i, k, l - 1);
        k = j;
        while (++k < C and T[i][k] != 'O') res += f_S(i, k, l - 1);
    }
    return res += f_N(i + 1, j, l);
}

int main() {
    while (cin >> R >> C >> L and not (R == 0 and C == 0 and L == 0)) {
        T = VVC(R, VC(C, '.'));
        int di, dj;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                char c;
                cin >> c;
                if (c == 'D') {
                    di = i;
                    dj = j;
                }
                if (c == 'P') {
                    pi = i;
                    pj = j;
                }
                if (c == 'O') old(i, j);
                if (T[i][j] != 'O') T[i][j] = c;
            }
        }
        F_S = F_N = VVVL(R, VVL(C, VL(L + 1, -1)));
        ll x = 0;
        for (int k = 0; k <= L; ++k) x += f_N(di, dj, k);
        if (x == 0) cout << "Good bye, Professor Dyer!" << endl;
        else cout << x << endl;
    }
}
