#include<iostream>
#include<vector>
#include<stack>
#include<sstream>
using namespace std;

using VE = vector<int>;
using ME = vector<VE>;
using VC = vector<char>;
using MC = vector<VC>;
using P = pair<int, int>;

int t, m, n, alfils;
ME tauler;
const VE dx = {1, 1, -1, -1};
const VE dy = {1, -1, 1, -1};

bool pos_ok (int a, int b) {
    return (a >= 0) and (a < n) and (b >= 0) and (b < m) and (tauler[a][b] != -1);
}

bool dfs (int i, int j) {
    int lliure = 1;
    int nombre = tauler[i][j];
    stack<P> S;
    tauler[i][j] = -1;
    S.push({i, j});
    while (not S.empty()) {
        int x = S.top().first;
        int y = S.top().second;
        S.pop();
        for (int k = 0; k < 4; ++k) {
            int a = x + dx[k];
            int b = y + dy[k];
            if (pos_ok(a, b)) {
                ++lliure;
                nombre += tauler[a][b];
                tauler[a][b] = -1;
                S.push({a, b});
            }
        }
    }
    if (alfils == -1) alfils = nombre/lliure;
    return nombre%lliure == 0 and alfils == nombre/lliure;
}

bool possible() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (tauler[i][j] != -1 and not dfs(i, j)) return false;
        }
    }
    return true;
}

int main () {
    cin >> t;
    for (int k = 0; k < t; ++k) {
        cin >> n >> m;
        tauler = ME(n, VE(m, -1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                string s;
                cin >> s;
                if (s != "X") {
                    stringstream num(s);
                    num >> tauler[i][j];
                }
            }
        }
        alfils = -1;
        cout << "Case " << k+1 << ": " << (possible() ? "yes":"no") << endl;
    }
}

