#include<iostream>
#include<vector>
#include<queue>
using namespace std;

using VE = vector<int>;
using ME = vector<VE>;
using VC = vector<char>;
using MC = vector<VC>;

const VE dx = {0, 1, 0, -1};
const VE dy = {1, 0, -1, 0};
int n, m, ti, tj;
MC fme;

bool pos_ok (int i, int j) {
    return (i >= 0) and (i < n) and (j >= 0) and (j < m) and (fme[i][j] != '#');
}

void bfs (int i, int j) {
    ME persones(n, VE(m, -1));
    ME dists(n, VE(m, -1));
    queue<pair<int, int> > Q;
    Q.push({i, j});
    int max_pers = -1;
    persones[i][j] = (fme[i][j] == 'P');
    dists[i][j] = 0;
    while (not Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        if (fme[x][y] == 'T') max_pers = max(max_pers, persones[x][y]);
        for (int k = 0; k < 4; ++k) {
            int a = x + dx[k];
            int b = y + dy[k];
            if (not pos_ok(a, b)) continue;
            if (dists[a][b] == -1) {
                dists[a][b] = dists[x][y] + 1;
                Q.push({a, b});
            }
            if (fme[a][b] != 'P') persones[a][b] = max(persones[a][b], persones[x][y]);
            else persones[a][b] = max(persones[a][b], 1 + persones[x][y]);
        }
    }
    if (max_pers != -1) cout << dists[ti][tj] << " " << max_pers << endl;
    else cout << "El telecos esta amagat." << endl;
}

int main () {
    while (cin >> n >> m) {
        fme = MC(n, VC(m));
