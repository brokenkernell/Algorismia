#include <iostream>
#include <vector>
#include <queue>
using namespace std;

using P = pair<int, int>;
using VP = vector<P>;
using MP = vector<VP>;
using VE = vector<int>;

MP G;
VE dist, origen;

void dijkstra (int o) {
    priority_queue<P> q;
    dist[o] = 0; origen[o] = o;
    q.push(P(0,o));
    while (not q.empty()) {
        int d = -q.top().first; int u = q.top().second; q.pop();
        if (d == dist[u]) {
            for (P arc : G[u]) {
                int cost = arc.second;
                int v = arc.first;
                int d2 = d + cost;
                if (P(d2, o) < P(dist[v], origen[v])) {
                    dist[v] = d2;
                    origen[v] = o;
                    q.push(P(-d2, v));
                }
            }
        }
    }
}

int main() {
    int casos; cin >> casos;
    
    for (int cas = 1; cas <= casos; ++cas) {
        cout << "Case #" << cas << endl;
        int n, m; cin >> n >> m;
        G = MP(n);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            G[a].push_back({b,c});
            G[b].push_back({a,c});
        }
        dist = VE(n, 1e9);
        origen = VE(n, -1);
        int k; cin >> k;
        for (int i = 0; i < k; ++i) {
            int ff; cin >> ff; dijkstra(ff);
        }
        int q; cin >> q;
        for (int i = 1; i <= q; ++i) {
            int desti; cin >> desti;
            cout << "To get to " << desti << ", distance " << dist[desti];
            cout << ", from city " << origen[desti] << "." << endl;
        }
        if (cas != casos) cout << endl;
    }
}
