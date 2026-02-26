#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

// Definició de l'estat per a la BFS: {posició_evariste, temps_mod_v}
using State = pair<int, int>;

// Funció per resoldre cada cas de prova
void solve() {
    int n; // Nombre de cantonades (corners)
    if (!(cin >> n)) return;

    int s, h; // Cantonada inicial d'Évariste (s) i la seva casa (h)
    cin >> s >> h;

    int m; // Nombre de carrers (streets)
    cin >> m;

    // El graf d'adjacència (llista)
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v_corner;
        cin >> u >> v_corner;
        // Els carrers són bidireccionals (two-way)
        adj[u].push_back(v_corner);
        adj[v_corner].push_back(u);
    }

    int v_sbire; // Nombre de cantonades patrullades pel sbire
    cin >> v_sbire;

    vector<int> sbire_path(v_sbire); // Camí cíclic del sbire
    for (int i = 0; i < v_sbire; ++i) {
        cin >> sbire_path[i];
    }
    
    // Convertim les cantonades (base 1) a índexs (base 0)
    // El sbire és a s_1 a l'instant 0, que correspon a l'índex 0
    // L'índex j del vector sbire_path correspon al sbire_time_mod_v = j
    auto get_sbire_pos = [&](int sbire_time_mod_v) {
        return sbire_path[sbire_time_mod_v];
    };
    
    auto get_sbire_pos_t_plus_1 = [&](int sbire_time_mod_v) {
        return sbire_path[(sbire_time_mod_v + 1) % v_sbire];
    };
    
    // --- Algorisme BFS ---

    // dist[cantonada][temps_mod_v] emmagatzema el temps mínim.
    // Inicialitzem amb un valor gran (infinit).
    const int INF = 1e9 + 7;
    vector<vector<int>> dist(n + 1, vector<int>(v_sbire, INF));

    queue<State> q;

    // L'estat inicial d'Évariste és 's' al temps 0.
    // El sbire és a s_1 (índex 0) al temps 0, i l'estat cíclic és 0 mod v.
    int initial_sbire_mod = 0;
    
    // Comprovem la condició inicial: s_1 != s
    if (s == sbire_path[0]) {
        // Aquesta situació no hauria de passar segons l'enunciat,
        // però si passés, Évariste ja estaria "foutu" al temps 0.
        // Tot i això, l'enunciat garanteix que s_1 != s
    }

    dist[s][initial_sbire_mod] = 0;
    q.push({s, initial_sbire_mod});

    int min_time = -1;

    while (!q.empty()) {
        State current_state = q.front();
        q.pop();

        int u = current_state.first; // Posició actual d'Évariste
        int k_mod_v = current_state.second; // Estat cíclic del sbire
        int t = dist[u][k_mod_v]; // Temps actual

        // 1. Condició d'arribada a casa
        if (u == h) {
            min_time = t;
            break;
        }

        // Si el temps actual és ja molt gran, podem considerar-lo inabastable
        if (t >= n * v_sbire) continue;

        // Estat del sbire a l'instant t+1
        int next_k_mod_v = (k_mod_v + 1) % v_sbire;
        int sbire_pos_t_plus_1 = get_sbire_pos_t_plus_1(k_mod_v); // Posició on serà el sbire a t+1

        // --- Transicions possibles a t+1 (durada 1 minut) ---

        // 1. Opció: Évariste es queda a la cantonada 'u' (stay)
        int next_u_stay = u;
        
        // RESTRICCIÓ DE CANTONADA: Évariste no pot ser a 'u' si el sbire hi és a t+1.
        if (next_u_stay != sbire_pos_t_plus_1) {
            if (t + 1 < dist[next_u_stay][next_k_mod_v]) {
                dist[next_u_stay][next_k_mod_v] = t + 1;
                q.push({next_u_stay, next_k_mod_v});
            }
        }

        // 2. Opció: Évariste es mou a una cantonada adjacent 'u'' (move)
        for (int next_u_move : adj[u]) {
            // RESTRICCIÓ DE CANTONADA: Évariste no pot arribar a 'next_u_move' si el sbire hi és a t+1.
            if (next_u_move == sbire_pos_t_plus_1) {
                continue; // Invàlid per restricció de cantonada
            }

            // RESTRICCIÓ DE CARRER: Évariste no pot anar de 'u' a 'next_u_move'
            // si el sbire recorre el carrer en direcció oposada (de 'next_u_move' a 'u')
            
            // Moviment del sbire a t: de get_sbire_pos(k_mod_v) a sbire_pos_t_plus_1
            int sbire_pos_t = get_sbire_pos(k_mod_v);

            // La vora que prohibeix el pas d'Évariste és (next_u_move -> u)
            if (sbire_pos_t_plus_1 == u && sbire_pos_t == next_u_move) {
                continue; // Invàlid per restricció de carrer
            }

            // Si totes les restriccions es compleixen, és una transició vàlida
            if (t + 1 < dist[next_u_move][next_k_mod_v]) {
                dist[next_u_move][next_k_mod_v] = t + 1;
                q.push({next_u_move, next_k_mod_v});
            }
        }
    }

    // --- Sortida (Output) ---

    if (min_time == -1) {
        cout << "Tu es foutu, Evariste!" << endl;
    } else {
        if (min_time == 1) {
            cout << "C'est une minute, Evariste!" << endl;
        } else {
            cout << "Ce sont " << min_time << " minutes, Evariste!" << endl;
        }
    }
}

int main() {
    // Optimització d'I/O (recomanat en programació competitiva)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Bucle per gestionar múltiples casos de prova
    while (cin.peek() != EOF) {
        solve();
    }

    return 0;
}
