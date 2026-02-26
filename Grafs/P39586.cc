#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

using VE = vector<int>;
using P = pair< int, int>;
using VP = vector<P>;
using MP = vector<VP>;

int n, m;
MP G;
VE camins;

int dijkstra (int x, int y) {
    VE dist(n, 1e9);
    camins = VE(n, 0);
    priority_queue<P> Q;
    Q.push({0, x});
    dist[x] = 0;
    camins[x] = 1;
    while (not Q.empty()) {
        int d = -Q.top().first;
        int u = Q.top().second;
        Q.pop();
        if (d == dist[u]) {
            for (P arc : G[u]) {
                int cost = arc.second;
                int v = arc.first;
                int d2 = d + cost;
                if (d2 < dist[v]) {
                    camins[v] = camins[u];
                    dist[v] = d2;
                    Q.push({-d2, v});
                }
                else if (d2 == dist[v]) camins[v] += camins[u];
            }
        }
    }
    return dist[y];
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
        if (d != 1e9) cout << "cost " << d << ", " << camins[y] << " way(s)" << endl;
        else cout << "no path from " << x << " to " << y << endl;
    }
}
