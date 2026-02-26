#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Funció per al primer pas de Kosaraju (DFS a G per omplir 'finish_stack')
void dfs1(int u, const vector<vector<int>>& adj, vector<bool>& visited, stack<int>& finish_stack) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs1(v, adj, visited, finish_stack);
        }
    }
    finish_stack.push(u);
}

// Funció per al segon pas de Kosaraju (DFS a G_T per trobar SCCs)
void dfs2(int u, const vector<vector<int>>& adj_T, vector<int>& scc_id, int current_scc) {
    scc_id[u] = current_scc;
    for (int v : adj_T[u]) {
        if (scc_id[v] == -1) {
            dfs2(v, adj_T, scc_id, current_scc);
        }
    }
}

// Funció per trobar nodes que poden assolir l'amontillado (BFS a G_T)
void find_unsafe_nodes(int n, const vector<vector<int>>& adj_T, const vector<int>& amontillado, vector<bool>& can_reach_amontillado) {
    vector<int> q;
    for (int start_node : amontillado) {
        if (!can_reach_amontillado[start_node]) {
            can_reach_amontillado[start_node] = true;
            q.push_back(start_node);
        }
    }

    int head = 0;
    while (head < q.size()) {
        int u = q[head++];
        for (int v : adj_T[u]) {
            if (!can_reach_amontillado[v]) {
                can_reach_amontillado[v] = true;
                q.push_back(v);
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, c, case_num = 1;
    while (cin >> n >> c) {
        vector<int> amontillado(c);
        for (int i = 0; i < c; ++i) {
            cin >> amontillado[i];
        }

        int m;
        cin >> m;
        vector<vector<int>> adj(n);
        vector<vector<int>> adj_T(n); // Graf transposat

        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj_T[v].push_back(u); // Construïm G_T
        }

        // --- 1. Trobar nodes insegurs (Condició 4) ---
        vector<bool> can_reach_amontillado(n, false);
        find_unsafe_nodes(n, adj_T, amontillado, can_reach_amontillado);

        // --- 2. Algorisme de Kosaraju (Trobar SCCs) ---
        
        // Pas 1: DFS a G per obtenir l'ordre de finalització
        stack<int> finish_stack;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs1(i, adj, visited, finish_stack);
            }
        }

        // Pas 2: DFS a G_T en l'ordre invers de finalització
        vector<int> scc_id(n, -1);
        int current_scc = 0;
        vector<int> scc_size;
        
        while (!finish_stack.empty()) {
            int u = finish_stack.top();
            finish_stack.pop();

            if (scc_id[u] == -1) {
                int old_size = scc_size.size();
                scc_size.push_back(0); // Mida inicial del nou SCC
                
                // Fem DFS a G_T per trobar tots els nodes en aquest SCC
                stack<int> scc_stack;
                scc_stack.push(u);
                scc_id[u] = current_scc;

                while(!scc_stack.empty()){
                    int curr = scc_stack.top();
                    scc_stack.pop();
                    scc_size[old_size]++;
                    for(int v : adj_T[curr]){
                        if(scc_id[v] == -1){
                            scc_id[v] = current_scc;
                            scc_stack.push(v);
                        }
                    }
                }
                current_scc++;
            }
        }

        // --- 3. Identificar SCCs "Segurs" ---
        int num_sccs = current_scc;
        vector<bool> scc_is_bad(num_sccs, false);
        for (int i = 0; i < n; ++i) {
            if (can_reach_amontillado[i]) {
                scc_is_bad[scc_id[i]] = true;
            }
        }

        // --- 4. Comptar Parelles ---
        long long total_pairs = 0;
        for (int j = 0; j < num_sccs; ++j) {
            if (!scc_is_bad[j]) {
                long long k = scc_size[j];
                // P(k, 2) = k * (k-1)
                total_pairs += k * (k - 1);
            }
        }

        // --- 5. Sortida ---
        cout << "Case #" << case_num++ << ": " << total_pairs << endl;
    }

    return 0;
}

