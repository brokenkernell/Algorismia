#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stack>
#include <algorithm> // per a std::min
#include <functional> // per a std::function (tot i que es pot evitar)

using namespace std;

// N serà el nombre total de possibilitats úniques
int N;
// Llista d'adjacència per al gràf d'implicacions (2*N nodes)
vector<vector<int>> adj;

// Variables per a l'algorisme de Tarjan (SCC)
vector<int> dfn;      // Temps de descobriment
vector<int> low;      // Valor "low-link"
vector<int> scc_id;   // A quin SCC pertany cada node
vector<bool> in_stack; // Per saber si un node és a la pila
stack<int> st;
int scc_count, time_stamp;

/**
 * Funció auxiliar per a 2-SAT.
 * Si N = total de possibilitats (ID 0 a N-1)
 * Node 'node' (0 <= node < N) representa la variable 'node' = true.
 * Node 'node + N' representa la variable 'node' = false (NOT node).
 * Aquesta funció retorna la negació d'un node.
 */
int neg(int node) {
    return (node < N) ? (node + N) : (node - N);
}

/**
 * Afegeix una clàusula (a OR b) al gràf.
 * 'a' i 'b' són els ID dels nodes per a les variables (0 <= a, b < N).
 * Això és equivalent a (NOT a => b) AND (NOT b => a).
 */
void add_clause(int a, int b) {
    // Aresta per (NOT a => b)
    adj[neg(a)].push_back(b);
    // Aresta per (NOT b => a)
    adj[neg(b)].push_back(a);
}

/**
 * Algorisme de Tarjan per trobar Components Fortament Connexos (SCC)
 */
void tarjan(int u) {
    dfn[u] = low[u] = ++time_stamp;
    st.push(u);
    in_stack[u] = true;

    for (int v : adj[u]) {
        if (!dfn[v]) { // Node v no visitat
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) { // Node v visitat i a la pila (una "back-edge")
            low[u] = min(low[u], dfn[v]);
        }
    }

    // Si u és l'arrel d'un SCC
    if (low[u] == dfn[u]) {
        ++scc_count;
        while (true) {
            int v = st.top();
            st.pop();
            in_stack[v] = false;
            scc_id[v] = scc_count;
            if (u == v) break;
        }
    }
}

/**
 * Resol un sol cas de prova
 */
void solve(int case_num) {
    // Mapa per convertir noms de possibilitats (string) a IDs (int)
    map<string, int> pos_to_id;
    // Per emmagatzemar els IDs de les possibilitats de cada categoria
    vector<vector<int>> categories;
    int current_id = 0;

    int c;
    cin >> c;
    cin.ignore(); // Consumeix el salt de línia després del número 'c'

    // Llegeix les categories
    for (int i = 0; i < c; ++i) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string possibility;
        vector<int> current_category;

        while (ss >> possibility) {
            // Assigna un nou ID si no l'hem vist mai
            if (pos_to_id.find(possibility) == pos_to_id.end()) {
                pos_to_id[possibility] = current_id++;
            }
            current_category.push_back(pos_to_id[possibility]);
        }
        categories.push_back(current_category);
    }

    // El nombre total de variables és el nombre d'IDs únics assignats
    N = current_id;

    // --- Reinicia les estructures del gràf i de Tarjan per a aquest cas ---
    adj.assign(2 * N, vector<int>());
    dfn.assign(2 * N, 0);
    low.assign(2 * N, 0);
    scc_id.assign(2 * N, 0);
    in_stack.assign(2 * N, false);
    while (!st.empty()) st.pop();
    scc_count = 0;
    time_stamp = 0;
    // --- ---

    // Afegeix les clàusules de categoria: (NOT a OR NOT b)
    for (const auto& category : categories) {
        for (size_t i = 0; i < category.size(); ++i) {
            for (size_t j = i + 1; j < category.size(); ++j) {
                int u = category[i]; // variable u
                int v = category[j]; // variable v
                
                // Clàusula (NOT u OR NOT v)
                // Els literals són neg(u) i neg(v)
                add_clause(neg(u), neg(v));
            }
        }
    }

    // Llegeix les condicions dels amics
    int f;
    cin >> f;
    for (int i = 0; i < f; ++i) {
        string name, cond1, cond2;
        cin >> name >> cond1 >> cond2;
        
        // Obtenim els IDs de les condicions
        // Assumim que les condicions existeixen al mapa (com diu l'enunciat)
        int u = pos_to_id[cond1];
        int v = pos_to_id[cond2];
        
        // Clàusula (u OR v)
        add_clause(u, v);
    }

    // Executa Tarjan a tots els nodes no visitats
    for (int i = 0; i < 2 * N; ++i) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // Comprova si hi ha contradiccions
    bool possible = true;
    for (int i = 0; i < N; ++i) {
        // Si la variable 'i' i 'NOT i' són al mateix SCC, és impossible.
        if (scc_id[i] == scc_id[neg(i)]) {
            possible = false;
            break;
        }
    }

    cout << "Case #" << case_num << ": " << (possible ? "yes" : "no") << endl;
}

int main() {
    // Optimitza la E/S de C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t; // Llegeix el nombre de casos de prova
    for (int i = 1; i <= t; ++i) {
        solve(i); // Resol cada cas
    }
    return 0;
}

