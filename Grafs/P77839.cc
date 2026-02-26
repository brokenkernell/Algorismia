#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring> // Per a memset
#include <algorithm>
#include <map>

using namespace std;

// Definim Infinit per als costos
const long long INF = 0x3f3f3f3f3f3f3f3f;

// Funció auxiliar per comprovar si una pàgina es pot teclejar
bool is_typable(int page, const bool broken[]) {
    int d1 = page / 100;
    int d2 = (page / 10) % 10;
    int d3 = page % 10;
    return !broken[d1 + '0'] && !broken[d2 + '0'] && !broken[d3 + '0'];
}

// Pas 1: Executa Dijkstra des d'una pàgina inicial
// Retorna un map amb els costos a totes les pàgines (100-899)
map<int, long long> run_dijkstra(int start_node, const bool broken[]) {
    map<int, long long> dist;
    for (int i = 100; i <= 899; ++i) {
        dist[i] = INF;
    }

    // Cua de prioritat per a Dijkstra: {cost, node}
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>> pq;

    // 1. Cost per estar a l'inici
    dist[start_node] = 0;
    pq.push({0, start_node});

    // 2. Cost per teclejar qualsevol pàgina (Cost 3)
    for (int t = 100; t <= 899; ++t) {
        if (is_typable(t, broken)) {
            if (dist[t] > 3) {
                dist[t] = 3;
                pq.push({3, t});
            }
        }
    }

    // 3. Executar Dijkstra amb moviments '+' i '-'
    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        // Prova el moviment '+'
        if (!broken['+']) {
            int v = (u == 899) ? 100 : u + 1;
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                pq.push({dist[v], v});
            }
        }

        // Prova el moviment '-'
        if (!broken['-']) {
            int v = (u == 100) ? 899 : u - 1;
            if (dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Taula per al TSP DP
// dp[mask][last_node_index]
// p <= 9, així que p+1 (nodes) <= 10.
// mask <= 1 << 9
long long dp[1 << 9][10];

int main() {
    // Optimització d'I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string broken_str;
    int p;

    while (cin >> broken_str >> p) {
        // Parsejar tecles trencades
        bool broken[256] = {false};
        string keys = broken_str.substr(7); // Saltar "broken:"
        for (char c : keys) {
            broken[c] = true;
        }

        // Llegir pàgines objectiu
        vector<int> targets(p);
        vector<int> nodes;
        nodes.push_back(100); // El node 0 és sempre la pàgina inicial

        for (int i = 0; i < p; ++i) {
            cin >> targets[i];
            // Només afegim si no és 100 (ja que comencem allà)
            if (targets[i] != 100) {
                nodes.push_back(targets[i]);
            }
        }

        // p_nodes és el nombre total de nodes al nostre graf TSP (100 + objectius)
        int p_nodes = nodes.size();
        // p_targets és el nombre d'objectius *diferents* de 100
        int p_targets = p_nodes - 1;

        // Pas 2: Construir la matriu de costos
        vector<vector<long long>> cost_matrix(p_nodes, vector<long long>(p_nodes));
        for (int i = 0; i < p_nodes; ++i) {
            map<int, long long> dists = run_dijkstra(nodes[i], broken);
            for (int j = 0; j < p_nodes; ++j) {
                cost_matrix[i][j] = dists[nodes[j]];
            }
        }

        // Pas 3: Resoldre el TSP
        memset(dp, 0x3f, sizeof(dp)); // Inicialitzar dp a INF

        // Cas base: cost 0 per estar al node 0 (100) amb mask 0
        dp[0][0] = 0;

        for (int mask = 0; mask < (1 << p_targets); ++mask) {
            for (int i = 0; i < p_nodes; ++i) { // i = node actual
                if (dp[mask][i] == INF) continue;

                // Intentar anar a un node objectiu 'j' (índex 1..p_targets)
                for (int j = 0; j < p_targets; ++j) {
                    // Si el node objectiu 'j' NO està a la màscara
                    if (!(mask & (1 << j))) {
                        int node_j_idx = j + 1; // Índex real a 'nodes' i 'cost_matrix'
                        if (cost_matrix[i][node_j_idx] != INF) {
                            int new_mask = mask | (1 << j);
                            long long new_cost = dp[mask][i] + cost_matrix[i][node_j_idx];
                            dp[new_mask][node_j_idx] = min(dp[new_mask][node_j_idx], new_cost);
                        }
                    }
                }
            }
        }

        // Pas 4: Trobar la resposta final
        long long min_cost = INF;
        int final_mask = (1 << p_targets) - 1;

        // Si no hi ha objectius (p.ex., p=1 i l'objectiu era 100), cost=0
        if (p_targets == 0) {
            min_cost = 0;
        } else {
            // El cost mínim és el mínim de tots els estats finals
            for (int i = 1; i < p_nodes; ++i) {
                min_cost = min(min_cost, dp[final_mask][i]);
            }
        }

        if (min_cost == INF) {
            cout << "no solution\n";
        } else {
            cout << min_cost << "\n";
        }
    }

    return 0;
}
