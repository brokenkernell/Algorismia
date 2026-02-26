#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
using namespace std;

using VE = vector<int>;
using P = pair< int, int>;
using VP = vector<P>;
using MP = vector<VP>;
using T = tuple< int, int, int>;

int n, m;
MP G;
VE passos;

int dijkstra (int x, int y) {
    VE dist(n, 1e9);
    passos = VE(n, 1e9);
    priority_queue<T> Q;
    Q.push(T(0, 0, x));
    dist[x] = 0;
    passos[x] = 0;
    while (not Q.empty()) {
        int d = -get<0>(Q.top());
        int p = -get<1>(Q.top());
        int u = get<2>(Q.top());
        Q.pop();
        if (d == dist[u] and p == passos[u]) {
            if (u == y) return d;
            for (P arc : G[u]) {
                int cost = arc.second;
                int v = arc.first;
                int d2 = d + cost;
                if (P(d2, p+1) < P(dist[v], passos[v])) {
                    dist[v] = d2;
                    passos[v] = p + 1;
                    Q.push(T(-d2, -p-1, v));
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
        if (d != -1) cout << "cost " << d << ", " << passos[y] << " step(s)" << endl;
        else cout << "no path from " << x << " to " << y << endl;
    }
}
