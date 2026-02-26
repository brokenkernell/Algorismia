#include<iostream>
#include<vector>
#include<queue>
using namespace std;

using VE = vector<int>;
using VVE = vector<VE>;
using VC = vector<char>;
using VVC = vector<VC>;
using P = pair<int, int>;

const VE dx = {0, 1, 0, -1};
const VE dy = {1, 0, -1, 0};

int n, m;
int dist = -1;
VVC mapa;

bool pos_ok (int a, int b) {
    return (a >= 0) and (a < n) and (b >= 0) and (b < m) and (mapa[a][b] != 'X');
}

void bfs (int i, int j) {
    VVE dists(n, VE(m, -1));
    dists[i][j] = 0;
    queue<P> Q;
    Q.push({i, j});
    while (not Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        if (mapa[x][y] == 't') dist = dists[x][y];
        for (int k = 0; k < 4; ++k) {
            int a = x + dx[k];
            int b = y + dy[k];
            if (pos_ok(a, b) and dists[a][b] == -1) {
                Q.push({a, b});
                dists[a][b] = dists[x][y] + 1;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    mapa = VVC(n, VC(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> mapa[i][j];
    }
    int i, j;
    cin >> i >> j;
    bfs(i - 1, j - 1);
    if (dist != -1) cout << "distancia maxima: " << dist << endl;
    else cout << "no es pot arribar a cap tresor" << endl;
}
