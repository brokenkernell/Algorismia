#include <iostream>
#include <queue>
#include <vector>
#include <stack>
using namespace std;

using VE = vector<int>;
using P = pair< int, int>;
using VP = vector<P>;
using MP = vector<VP>;

int n, m;
MP G;
VE pare;

int dijkstra (int x, int y) {
    VE dist(n, 1e9);
    pare = VE(n, -1);
    priority_queue<P> Q;
    dist[x] = 0;
    Q.push({0, x});
    while (not Q.empty()) {
        int d = -Q.top().first;
        int u = Q.top().second;
        Q.pop();
        if (d == dist[u]) {
            if (u == y) return d;
            for (P arc : G[u]) {
                int cost = arc.second;
                int v = arc.first;
                int d2 = d + cost;
                if (d2 < dist[v]) {
                    dist[v] = d2;
                    pare[v] = u;
                    Q.push({-d2, v});
                }
            }
        }
    }
    return -1;
}

int main() {
    while (cin >> n >> m) {
        G = MP(n);
        for (int i = 0; i < m; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            G[u].push_back({v, c});
        }
        int x, y;
        cin >> x >> y;
        int d = dijkstra(x, y);
        if (d != -1) {
            stack<int> S;
            while (y != -1) {
                S.push(y);
                y = pare[y];
            }
            cout << S.top();
            S.pop();
            while (not S.empty()) {
                cout << " " << S.top();
                S.pop();
            }
            cout << endl;
        }
        else cout << "no path from " << x << " to " << y << endl;
    }
}
