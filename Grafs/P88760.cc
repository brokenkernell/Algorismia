#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;

struct Roca {
    double x, y, r;
};

using VE = vector<int>;
using VVE = vector<VE>;
using VR = vector<Roca>;

VVE salts;
int n;

double dist_roques (Roca r1, Roca r2) {
    return sqrt((r1.x-r2.x)*(r1.x-r2.x) + (r1.y-r2.y)*(r1.y-r2.y)) - r1.r - r2.r;
}

int bfs ( int x0) {
    VE distancies(n, -1);
    queue<int> Q;
    Q.push(x0);
    distancies[x0] = 0;
    while (not Q.empty()) {
        int x = Q.front();
        Q.pop();
        if (x == n-1) return distancies[x];
        for (int y : salts[x]) {
            if (distancies[y] == -1) {
                distancies[y] = distancies[x] + 1;
                Q.push(y);
            }
        }
    }
    return -1;
}

int main () {
    double d;
    while (cin >> n >> d) {
        VR roques(n);
        salts = VVE(n);
        for (int i = 0; i < n; ++i) {
            cin >> roques[i].x >> roques[i].y >> roques[i].r;
            for (int j = i-1; j >= 0; --j) {
                if (dist_roques(roques[i], roques[j]) <= d) {
                    salts[i].push_back(j);
                    salts[j].push_back(i);
                }
            }
        }
        int dist = bfs(0);
        if (dist != -1) cout << dist << endl;
        else cout << "Xof!" << endl;
    }
}
